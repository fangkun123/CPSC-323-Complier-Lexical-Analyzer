operator = "*+-=/><%"
separator = "'(){}[],:;"
keywords = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do", "doend","for", "forend", "input", "output", "and", "or", "function" }

def isKeyword(buffer):
    for i in keywords:
        if i == buffer:
            return True
    return False

def isOperator(ch):
    for i in operator:
        if i == ch:
            return True
    return False

def isSeparator(ch):
    for i in separator:
        if i == ch:
            return True
    return False

def isNumber(buffer, currentIndex):
    count = 0
    while count < currentIndex:
        if not buffer[count].isdigit():
            return False
        count += 1
    return True

def isReal(buffer, currentIndex):
    str = convert(buffer)
    found = str.find(".")
    if found != -1:
        index = 0
        while index < found:
            if not str[index].isdigit():
                return false
            index += 1

        index = found + 1
        while index < currentIndex:
            if not str[index].isdigit():
                return false
            index += 1
        return True
    else:
        return False

def convert(buffer):
    new = ""
    for i in buffer:
        new += i
    return new




def main():
    isComments = False
    detection = [' '] * 2
    x = 0

    currentIndex = 0

    hasSep = False
    hasOpe = False

    endOperator = False
    endSeparator = False
    endNumber = False
    endReal = False
    endIdentifier = False

    buffer = ['\0'] * 15
    j = 0

    filename = input("Please enter file name where you want to read: ")
    outputFileName = input("Please enter file name where you want to store output: ")
    outputFile = open(outputFileName,'a')
    with open(filename) as fin:
        print("TOKENS               Lexemes")
        outputFile.write("TOKENS               Lexemes\n")
        while True:
            ch = fin.read(1)

            if not ch:
                fin.close()
                outputFile.close()
                exit(0)
            else:
                if ch == '!':
                    detection[x] = ch
                    x += 1
                    if detection[1] == ch:
                        isComments = False
                        x = 0
                        detection = '\0'
                    else:
                        isComments = True

                if not isComments:
                    if isSeparator(ch):
                        hasSep = True
                        endSeparator = True
                    if isOperator(ch):
                        hasOpe = True
                        endOperator = True
                    if ch.isalnum() or ch == '$' or ch == '.':
                        buffer[j] = ch
                        j += 1
                        currentIndex += 1
                    elif j != 0 and (ch == ' ' or ch == '\n' or hasSep or hasOpe or ch == None):
                        i = 0
                        while i < len(buffer):
                            if i >= j:
                                buffer[i] = '\0'
                            i += 1
                        j = 0
                        if isKeyword(buffer):
                            print("KEYWORD         =     " + convert(buffer))
                            outputFile.write("KEYWORD         =     " + convert(buffer) + "\n")
                        elif isNumber(buffer, currentIndex):
                            endNumber = True
                        elif isReal(buffer,currentIndex):
                            endReal = True
                        else:
                            if not buffer[0].isdigit():
                                endIdentifier = True
                        currentIndex = 0

                    if endIdentifier:
                        print("IDENTIFIER      =     " + convert(buffer))
                        outputFile.write("IDENTIFIER      =     " + convert(buffer)+ "\n")
                        endIdentifier = False
                    if endNumber:
                        print("NUMBER          =     " + convert(buffer))
                        outputFile.write("NUMBER          =     " + convert(buffer)+ "\n")
                        endNumber = False
                    if endReal:
                        print("REAL            =     " + convert(buffer))
                        outputFile.write("REAL            =     " + convert(buffer)+ "\n")
                        endReal = False
                    if endSeparator:
                        print("SEPARATOR       =     " + ch)
                        outputFile.write("SEPARATOR       =     " + ch + "\n")
                        endSeparator = False
                    if endOperator:
                        print("OPERATOR        =     " + ch)
                        outputFile.write("OPERATOR        =     " + ch + "\n")
                        endOperator = False



main()

