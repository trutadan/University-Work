from grammar import Grammar
from recursive_descendant import RecursiveDescendant

if __name__ == '__main__':
    filename = "gtest.txt"
    grammar = Grammar(filename)

    parser = RecursiveDescendant(grammar)

    actions_sequence_example = ("exp adv exp adv exp mi at mi at adv adv exp mi at mi at adv mi back at back back at "
                                "back at adv exp mi at mi at adv adv exp mi at mi at adv success")

    actions = actions_sequence_example.split()

    print("Parsing the sequence w = aacbc...")
    print(parser)
    for index in range(len(actions)):
        if actions[index] == "exp":
            parser.expand()
        elif actions[index] == "adv":
            parser.advance()
        elif actions[index] == "mi":
            parser.momentary_insuccess()
        elif actions[index] == "back":
            parser.back()
        elif actions[index] == "at":
            parser.another_try()
        elif actions[index] == "success":
            parser.success()
        else:
            print("error")

    parser = RecursiveDescendant(grammar)

    print("\nParsing the sequence w = b...")
    print(parser)
    parser.expand()
    parser.momentary_insuccess()
    parser.another_try()
    parser.momentary_insuccess()
    parser.another_try()
    parser.momentary_insuccess()
    parser.another_try()