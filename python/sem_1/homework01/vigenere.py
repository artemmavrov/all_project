def encrypt_vigenere(plaintext: str, keyword: str) -> str:
    """
    Encrypts plaintext using a Vigenere cipher.

    >>> encrypt_vigenere("PYTHON", "A")
    'PYTHON'
    >>> encrypt_vigenere("python", "a")
    'python'
    >>> encrypt_vigenere("ATTACKATDAWN", "LEMON")
    'LXFOPVEFRNHR'
    """
    ciphertext = ""
    # PUT YOUR CODE HERE
    l_keyword = len(keyword)
    for i in range(len(plaintext)):
        number = ord(plaintext[i])
        key = ord(keyword[i % l_keyword])
        if 65 <= key <= 90:
            key -= 65
        elif 97 <= key <= 122:  # где 97 и 122 крайние индекса строчных букв
            key -= 97
        else:
            key = 0
        if 65 <= number <= 90:  # где 65 и 90 крайние индекса заглавных букв
            number_new = number + key
            if number_new > 90:
                number_new -= 26
        elif 97 <= number <= 122:
            number_new = number + key
            if number_new > 122:
                number_new -= 26
        else:
            number_new = number
        ciphertext += chr(number_new)
    return ciphertext


def decrypt_vigenere(ciphertext: str, keyword: str) -> str:
    """
    Decrypts a ciphertext using a Vigenere cipher.

    >>> decrypt_vigenere("PYTHON", "A")
    'PYTHON'
    >>> decrypt_vigenere("python", "a")
    'python'
    >>> decrypt_vigenere("LXFOPVEFRNHR", "LEMON")
    'ATTACKATDAWN'
    """
    plaintext = ""
    # PUT YOUR CODE HERE
    l_keyword = len(keyword)
    for i in range(len(ciphertext)):
        number = ord(ciphertext[i])
        key = ord(keyword[i % l_keyword])
        if 65 <= key <= 90:  # где 65 и 90 крайние индекса заглавных букв
            key -= 65
        elif 97 <= key <= 122:  # где 97 и 122 крайние индекса строчных букв
            key -= 97
        else:
            key = 0
        if 65 <= number <= 90:
            number_new = number - key
            if number_new < 65:
                number_new += 26
        elif 97 <= number <= 122:
            number_new = number - key
            if number_new < 97:
                number_new += 26
        else:
            number_new = number
        plaintext += chr(number_new)
    return plaintext
