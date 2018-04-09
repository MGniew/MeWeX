from __future__ import absolute_import, division, print_function


import itertools as itt
import os
import logging
import subprocess as subp
from tempfile import NamedTemporaryFile

import six

from . import _enums as en


__all__ = 'call_mewex', 'MewexError'


_LOG = logging.getLogger('mewexlib')


def call_mewex(input_files,
               output_file,
               ranker_func=
               en.RankerFunction.w_specific_exponential_correlation,
               dispersion_func=None,
               wccl_rels=en.DEFAULT_WCCL_RELATIONS,
               num_kbest=100,
               extract_orths=True,
               tagset_name='nkjp',
               reader_name='ccl',
               mewex_exec='WebTool'):
    """
    Call Mewex application using the input, output and parameters using
    arguments passed to the function.

    All optional parameters provide reasonable defaults used my the MeWeX web
    application.

    ``input_files`` is either a string naming a file listing paths to input
    files for mewex, or a tuple of strings listing those paths. In the latter
    case, the filenames from the tuple will be written to a temporary file, as
    mewex requires that format.

    ``output_file`` is the path to a non-existent file where kbest output will
    be written.

    ``ranker_func`` is an enumerated value from
    :class:`mewexlib._enums.RankerFunction`, which lists all ranker function
    configurations usable by the MeWeX web application.

    ``dispersion_func`` is an enumerated value from
    :class:`mewexlib._enums.DispersionFunction`, which lists all dispersion
    function configurations usable by the MeWeX web application. It may be
    ``None`` to not use a dispersion function, especially if there is only one
    input file.

    ``wccl_rels`` is a set of enumerated values from
    :class:`mewexlib._enums.WCCLRelation` which lists all WCCL
    relation-extracting operators usable by the MeWeX web application. The
    default set is provided as :data:`mewexlib._enums.DEFAULT_WCCL_RELATIONS`.

    ``num_kbest`` is the maximum number of kbest items written to the output;
    default 100. Use ``-1`` to disable limiting.

    If ``extract_orths`` is ``True`` (the default), orths are extracted from
    input.

    ``tagset_name`` is the name of corpus2 tagset used by mewex; ``nkjp`` by
    default.

    ``reader_name`` is the name of corpus2 reader used by mewex; ``ccl`` by
    default.

    ``mewex_exec`` is the path to the mewex executable binary (or just the name
    if it's on ``$PATH``); ``WebTool`` by default.

    If mewex executable returns with an error, status, a :exc:`MewexError`
    exception is raised.
    """

    with _InputFiles(input_files) as input_arg:
        ranker_args = ranker_func.to_args_tuple()
        dispersion_args = (
            ()
            if dispersion_func is None
            else dispersion_func.to_args_tuple()
        )
        rel_args_flat = itt.chain.from_iterable(
            relen.to_args_tuple()
            for relen in wccl_rels
        )

        call = tuple(itt.chain(
            (
                mewex_exec,
                '-I', input_arg,
                '-K', output_file,
                '-T', tagset_name,
                '-R', reader_name,
                '-k', str(num_kbest),
                '-o', str(int(bool(extract_orths))),
            ),
            ranker_args,
            dispersion_args,
            rel_args_flat,
        ))

        _LOG.info('Calling %s with parameters: %r', mewex_exec, call)

        proc = subp.Popen(call, stderr=subp.PIPE)
        proc_err = proc.communicate()[1].decode('utf8')

    if proc.returncode != 0:
        raise MewexError(proc.returncode, proc_err)

    _LOG.info(
        '%s returned successfully with message:\n%s',
        mewex_exec,
        proc_err,
    )


class MewexError(Exception):

    def __init__(self, error_code, stderr_text):
        super(MewexError, self).__init__(error_code, stderr_text)
        self._err_code = error_code
        self._err_text = stderr_text

    def __repr__(self):
        return '{}(error_code={!r}, stderr_text={!r})'.format(
            self.__class__.__name__,
            self._err_code,
            self._err_text,
        )

    def __str__(self):
        return 'Mewex failed with error code: {}\n{}'.format(
            self._err_code,
            _tail_stderr_for_exc(self._err_text),
        )


def _tail_stderr_for_exc(stderr_text):
    # Find the eleventh newline to print the last ten lines
    end = len(stderr_text)
    found = 0

    while found < 11 and end > 0:
        end = stderr_text.rfind(u'\n', 0, end)
        found += 1

    return u'(...)\n' + stderr_text[end:].lstrip() if end > 0 else stderr_text


class _InputFiles(object):

    def __init__(self, inputs):
        self._inputs = inputs
        self._fname = None

    def __enter__(self):
        if isinstance(self._inputs, six.string_types):
            # Just return a (possible) filename
            return self._inputs

        with NamedTemporaryFile('w', suffix='-mewexlist', delete=False) as tf:
            self._fname = tf.name

            for input_name in self._inputs:
                print(input_name, file=tf)

        return self._fname

    def __exit__(self, exc_type, exc_value, exc_tb):
        if self._fname is not None:
            os.remove(self._fname)
