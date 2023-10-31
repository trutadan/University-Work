import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

public class LexicalAnalyzer {
    private final SymbolTable symbolTable = new SymbolTable(100);
    private final ProgramInternalForm programInternalForm = new ProgramInternalForm();

    private final String inputFile;
    private final String programInternalFormOutputFile;
    private final String symbolTableOutputFile;

    private final ArrayList<String> separators = new ArrayList<>(
            List.of("{", "}", "(", ")", "[", "]", ":", ";", ",")
    );
    private final ArrayList<String> operators = new ArrayList<>(
            List.of("+", "-", "*", "/", "%", "<=", ">=", "==", "!=", "<", ">", "=")
    );
    private final ArrayList<String> reservedWords = new ArrayList<>(
            List.of("array", "bool", "int", "char", "nil", "string",
                    "elif", "if", "else" ,"do", "end", "for", "while", "break",
                    "gets", "puts", "cuts", "to_i", "start", "stop",
                    "and", "not", "or", "false", "true", "in")
    );

    public LexicalAnalyzer(String inputFile) {
        this.inputFile = inputFile;
        this.programInternalFormOutputFile = "PIF.out";
        this.symbolTableOutputFile = "ST.out";
    }

    public LexicalAnalyzer(String inputFile, String programInternalFormOutputFile, String symbolTableOutputFile) {
        this.inputFile = inputFile;
        this.programInternalFormOutputFile = programInternalFormOutputFile;
        this.symbolTableOutputFile = symbolTableOutputFile;
    }

    public SymbolTable getSymbolTable() {
        return this.symbolTable;
    }

    public ProgramInternalForm getProgramInternalForm() {
        return this.programInternalForm;
    }

    private boolean isSeparator(String token) {
        return this.separators.contains(token);
    }

    private boolean isOperator(String token) {
        return this.operators.contains(token);
    }

    private boolean isReservedWord(String token) {
        return this.reservedWords.contains(token);
    }

    private boolean isIdentifier(String token) {
        return Pattern.matches("([a-zA-Z_][a-zA-Z0-9_]*)", token);
    }

    private boolean isIntegerConstant(String token) {
        return Pattern.matches("0|([+-]?[1-9][0-9]*)", token);
    }

    private boolean isCharConstant(String token) {
        return Pattern.matches("'[a-zA-Z0-9]'", token);
    }

    private boolean isStringConstant(String token) {
        return Pattern.matches("\"([a-zA-Z0-9 ]+)\"|\"\"", token);
    }

    private boolean isBooleanConstant(String token) {
        return Pattern.matches("true|false", token);
    }

    private List<String> detect(String line) {
        List<String> tokens = new ArrayList<>();

        StringBuilder currentToken = new StringBuilder();
        // detect string and char constants
        boolean insideString = false;
        boolean insideCharConstant = false;

        for (int index = 0; index < line.length(); index++) {
            char character = line.charAt(index);
            String characterAsString = String.valueOf(character);

            if (insideString) {
                currentToken.append(character);
                if (characterAsString.equals("\"")) {
                    // reset the boolean
                    insideString = false;
                    // add string constant to the tokens list
                    tokens.add(currentToken.toString());
                    // clear the current token
                    currentToken.setLength(0);
                }
            } else if (insideCharConstant) {
                currentToken.append(character);
                if (characterAsString.equals("'")) {
                    // reset the boolean
                    insideCharConstant = false;
                    // add character constant to the tokens list
                    tokens.add(currentToken.toString());
                    // clear the current token
                    currentToken.setLength(0);
                }
            } else {
                String twoCharOperator = index + 1 < line.length() ? characterAsString + line.charAt(index + 1) : "";

                if (this.isOperator(twoCharOperator)) {
                    if (!currentToken.isEmpty()) {
                        tokens.add(currentToken.toString());
                    }
                    tokens.add(twoCharOperator);
                    // move to the next character
                    index++;
                    currentToken.setLength(0);
                } else if (this.isSeparator(characterAsString)|| this.isOperator(characterAsString)) {
                    if (!currentToken.isEmpty())
                        tokens.add(currentToken.toString());
                    // if it is a separator add it to the tokens list
                    tokens.add(characterAsString);
                    // clear the current token
                    currentToken.setLength(0);
                } else if (characterAsString.equals("\"")) {
                    insideString = true;
                    // start constructing the string constant
                    currentToken.append(character);
                } else if (characterAsString.equals("'")) {
                    insideCharConstant = true;
                    currentToken.append(character);
                // exclude space, newline, tab separators from the tokens list
                } else if (!characterAsString.matches("[\t\n ]")) {
                    currentToken.append(character);
                } else {
                    // handle the rest of the alphanumeric characters
                    if (!currentToken.isEmpty()) {
                        tokens.add(currentToken.toString());
                        currentToken.setLength(0);
                    }
                }
            }
        }

        if (!currentToken.isEmpty())
            tokens.add(currentToken.toString());

        return tokens;
    }

    private Integer classify(String token) throws LexicalErrorException {
        // category 0 for boolean constants
        if (isBooleanConstant(token))
            return 0;

        // category 2 for reserved words
        if (isReservedWord(token)) {
            return 2;
        }

        // category 0 for integer/char/string constants
        if (isIntegerConstant(token) || isCharConstant(token) || isStringConstant(token)) {
            return 0;
        }

        // category 1 for identifiers
        if (isIdentifier(token)) {
            return 1;
        }

        // category 3 for separators
        if (isSeparator(token)) {
            return 3;
        }

        // category 4 for operators
        if (isOperator(token)) {
            return 4;
        }

        // if the token doesn't match any known category, throw a LexicalErrorException
        throw new LexicalErrorException("Unrecognized token - " + token);
    }

    private void codify(String token, Integer category) {
        Pair<Integer, Integer> positionInSymbolTable = new Pair<>(-1, -1);

        if (category == 0 || category == 1) {
            positionInSymbolTable = this.symbolTable.add(token);
        }

        this.programInternalForm.add(token, positionInSymbolTable);
    }

    public void scan() {
        BufferedReader reader;
        int lineNumber = 1;
        boolean lexicallyCorrect = true;

        try {
            reader = new BufferedReader(new FileReader(this.inputFile));
            String line = reader.readLine();

            while (line != null) {
//                System.out.println(line);

                List<String> tokens = this.detect(line);
//                System.out.println(tokens);

                for (String token : tokens) {
                    try {
                        int category = this.classify(token);
                        this.codify(token, category);
                    } catch (LexicalErrorException exception) {
                        lexicallyCorrect = false;
                        System.out.println("Lexical error on line " + lineNumber + ": " + exception.getMessage());
                    }
                }

                // read next line
                line = reader.readLine();
                lineNumber++;
            }

            reader.close();
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }

        if (lexicallyCorrect)
            System.out.println("The program is lexically correct!");

        // output the symbol table to the symbolTableOutputFile
        try (PrintWriter writer = new PrintWriter(this.symbolTableOutputFile)) {
            writer.println(this.symbolTable);
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }

        // output the program internal form to the programInternalFormOutputFile
        try (PrintWriter writer = new PrintWriter(this.programInternalFormOutputFile)) {
            writer.println(this.programInternalForm);
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }
    }
}