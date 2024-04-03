import re

# Define regular expressions for terminal symbols
patterns = {
    'let': r'\blet\b',
    'in': r'\bin\b',
    'fn': r'\bfn\b',
    'aug': r'\baug\b',
    'where': r'\bwhere\b',
    'or': r'\bor\b',
    'and': r'\band\b',
    'rec': r'\brec\b',
    'within': r'\bwithin\b',
    'true': r'\btrue\b',
    'false': r'\bfalse\b',
    'nil': r'\bnil\b',
    'dummy': r'\bdummy\b',
    'not': r'\bnot\b',
    'gr': r'\bgr\b',
    'ge': r'\bge\b',
    'ls': r'\bls\b',
    'le': r'\ble\b',
    'eq': r'\beq\b',
    'ne': r'\bne\b',
    'neg': r'\bneg\b',
    'tau': r'\btau\b',
    '->': r'\b->\b',
    '\+': r'\+',
    '-': r'\-',
    '\*': r'\*',
    '/': r'\/',
    '\*\*': r'\*\*',
    '@': r'\@',
    '\|': r'\|',
    ',': r'\,',
    '\(': r'\(',
    '\)': r'\)',
    '=': r'=',
    'gr': r'>',
    'ge': r'>=',
    'ls': r'<',
    'le': r'<=',
    'eq': r'==',
    'ne': r'!=',
    'IDENTIFIER': r'[a-zA-Z_][a-zA-Z0-9_]*',
    'INTEGER': r'\d+',
    'STRING': r'\".*?\"'
}

# Compile regular expressions
patterns = {key: re.compile(value) for key, value in patterns.items()}

# Function to tokenize input string
def tokenize(input_str):
    tokens = []
    pos = 0
    while pos < len(input_str):
        match = None
        for token_type, pattern in patterns.items():
            match = pattern.match(input_str, pos)
            if match:
                value = match.group(0)
                if token_type != 'WS':  
                    tokens.append((token_type, value))
                pos = match.end()
                break
        if not match:
            raise Exception('Invalid input at position ' + str(pos) + ': ' + input_str[pos:])
    return tokens

# Test the scanner
input_str = 'let x = 10 in fn y => y + 5'
tokens = tokenize(input_str)
print(tokens)
