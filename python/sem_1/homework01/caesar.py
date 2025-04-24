import typing as tp


def encrypt_caesar(plaintext: str, shift: int = 3) -> str:
    """
    Encrypts plaintext using a Caesar cipher.

    >>> encrypt_caesar("PYTHON")
    'SBWKRQ'
    >>> encrypt_caesar("python")
    'sbwkrq'
    >>> encrypt_caesar("Python3.6")
    'Sbwkrq3.6'
    >>> encrypt_caesar("")
    ''
    """
    ciphertext = ""
    # PUT YOUR CODE HERE

    for i in range(len(plaintext)):
        number = ord(plaintext[i])
        if 65 <= number <= 90:  # где 65 и 90 крайние индекса заглавных букв
            number_new = number + shift
            if number_new > 90:
                number_new -= 26
        elif 97 <= number <= 122:  # где 97 и 122 крайние индекса строчных букв
            number_new = number + shift
            if number_new > 122:
                number_new -= 26
        else:
            number_new = number
        ciphertext += chr(number_new)
    return ciphertext


def decrypt_caesar(ciphertext: str, shift: int = 3) -> str:
    """
    Decrypts a ciphertext using a Caesar cipher.

    >>> decrypt_caesar("SBWKRQ")
    'PYTHON'
    >>> decrypt_caesar("sbwkrq")
    'python'
    >>> decrypt_caesar("Sbwkrq3.6")
    'Python3.6'
    >>> decrypt_caesar("")
    ''
    """
    plaintext = ""
    # PUT YOUR CODE HERE

    for i in range(len(ciphertext)):
        number = ord(ciphertext[i])
        if 65 <= number <= 90:  # где 65 и 90 крайние индекса заглавных букв
            number_new = number - shift
            if number_new < 65:
                number_new += 26
        elif 97 <= number <= 122:  # где 97 и 122 крайние индекса строчных букв
            number_new = number - shift
            if number_new < 97:
                number_new += 26
        else:
            number_new = number
        plaintext += chr(number_new)
    return plaintext


def caesar_breaker_brute_force(ciphertext: str, dictionary: tp.Set[str]) -> int:
    """
    Brute force breaking a Caesar cipher.
    """
    best_shift = 0
    # PUT YOUR CODE HERE
    max_word_count = 0
    for shift in range(26):
        decrypted = decrypt_caesar(ciphertext, shift)
        word_count = 0

        for word in decrypted.split():
            if word in dictionary:
                word_count += 1

        if word_count > max_word_count:
            max_word_count = word_count
            best_shift = shift
    return best_shift
