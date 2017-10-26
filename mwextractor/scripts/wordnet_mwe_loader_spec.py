#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import MySQLdb


class Lemma(object):

    def __init__(self, p_id, p_is_abstract, p_pos, p_lemma):
        self.m_id = p_id
        self.m_is_abstract = p_is_abstract
        self.m_pos = p_pos
        self.m_lemma = p_lemma

    def to_csv(self):
        return \
            str(self.m_id) + '\t' + \
            str(self.m_is_abstract) + '\t' + \
            self.m_pos + '\t' + self.m_lemma

    @staticmethod
    def csv_header():
        return "DB ID\tIs abstract?\tPart of Speech\tLemma"


def decode_pos(p_pos_id):
    if p_pos_id == 1:
        return "verb"
    elif p_pos_id == 2:
        return "subst"
    elif p_pos_id == 3:
        return "3"
    elif p_pos_id == 4:
        return "adj"
    elif p_pos_id == 5:
        return "eng verb"
    elif p_pos_id == 6:
        return "eng subst"
    elif p_pos_id == 7:
        return "eng 3"
    elif p_pos_id == 8:
        return "eng adj"
    return "eng: " + str(p_pos_id)


def decode_abstraction(p_is_abstract):
    return True if p_is_abstract == 1 else False


def load_mwes_from_wordnet(p_host, p_user, p_password, p_db, p_polish=True, p_english=True):
    db = MySQLdb.connect(
        host=p_host,
        user=p_user,
        passwd=p_password,
        db=p_db,
        charset="utf8")
    cursor = db.cursor()

    if not p_polish and not p_english:
        return []

    first = "1" if p_polish else "5"
    second = "8" if p_english else "4"
    
    cursor.execute(
        "SELECT l.ID, s.isabstract, l.pos, l.lemma "
        "FROM lexicalunit l, synset s, unitandsynset u "
        "WHERE l.ID = u.LEX_ID AND u.SYN_ID = s.ID AND l.lemma LIKE '%_ %_' "
        "AND l.pos >= " + first + " AND l.pos <= " + second + " "
        "AND l.comment LIKE '%##K: specj%' "
        "ORDER BY l.ID ASC;")

    row_count = int(cursor.rowcount)

    mwes = []
    for i in range(0, row_count):
        row = cursor.fetchone()
        mwes.append(
            Lemma(
                row[0],
                decode_abstraction(row[1]),
                decode_pos(row[2]),
                row[3]
            )
        )

    return mwes


def main(
        p_output_file,
        p_host="localhost",
        p_user="root",
        p_password="none",
        p_db="wordnet"):
    mwes = load_mwes_from_wordnet(p_host, p_user, p_password, p_db)

    with codecs.open(p_output_file, "w", "utf8") as out_file:
        out_file.write(Lemma.csv_header() + '\n'.encode("utf-8"))
        for mwe in mwes:
            out_file.write(mwe.to_csv() + '\n'.encode("utf-8"))


"""
This script loads mwes from wordnet databse

usage: script.py output_file database_password database_name
"""
if __name__ == "__main__":
    main(sys.argv[1], p_password=sys.argv[2], p_db=sys.argv[3])
