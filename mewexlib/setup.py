# coding: utf8
from setuptools import setup

if __name__ == '__main__':
    setup(
        name='mewexlib',
        version='0.2',
        description='Library for using MeWeX as part of another program',

        author='Michał Kaliński',
        author_email='michal.kalinski@pwr.edu.pl',

        packages=['mewexlib'],
        package_data={
            'mewexlib': [
                'data/mlp_model.txt',
                'data/relations/*.ccl',
            ],
        },

        install_requires=['six>=1.10', 'enum34>=1.1.2;python_version<"3.4"'],
        zip_safe=False,
    )
