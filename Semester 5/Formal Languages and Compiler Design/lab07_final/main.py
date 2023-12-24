from grammar import Grammar
from recursive_descendant import RecursiveDescendant


def parse_grammar(grammar_file_name: str, sequence_file_name: str, output_file_name: str):
    grammar = Grammar(grammar_file_name)
    parser = RecursiveDescendant(grammar, sequence_file_name, output_file_name)
    parser.parse()


if __name__ == '__main__':
    parse_grammar("g1/grammar.txt", "g1/good_sequence.txt", "g1/good_output.txt")
    parse_grammar("g1/grammar.txt", "g1/bad_sequence.txt", "g1/bad_output.txt")

    parse_grammar("g2/grammar.txt", "g2/sequence.txt", "g2/output.txt")
