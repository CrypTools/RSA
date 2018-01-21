import random


'''
    Euclid's algorithm for determining the greatest common divisor
    Use iteration to make it faster for larger integers
'''
def gcd(a, b):
    while b != 0:
        # t = b
        # b = a % b
        # a = t
        a, b = b, a % b
    return a

'''
    Euclid's extended algorithm for finding the multiplicative inverse of two
    numbers
'''
def multiplicative_inverse(e, phi):
    d = 0
    x1 = 0
    x2 = 1
    y1 = 1
    temp_phi = phi

    while e > 0:
        temp1 = temp_phi/e
        temp2 = temp_phi - temp1 * e
        temp_phi = e
        e = temp2

        x = x2- temp1* x1
        y = d - temp1 * y1

        x2 = x1
        x1 = x
        d = y1
        y1 = y

    if temp_phi == 1:
        return d + phi

'''
    Tests to see if a number is prime.
'''
def is_prime(num):
    if num == 2:
        return True
    # prime nums can't be less divisible by two (except 2)
    if num < 2 or num % 2 == 0:
        return False
    for n in xrange(3, int(num**0.5)+2, 2):
        if num % n == 0:
            return False
    return True

def generate_keypair(prime_one, prime_two):
    #
    if not (is_prime(prime_one) and is_prime(prime_two)):
        raise ValueError('Both numbers must be prime.')
    elif prime_one == prime_two:
        raise ValueError('prime_one and prime_two cannot be equal')
    # n = prime_one * prime_two
    p_times_q = prime_one * prime_two #n

    # Phi () is the totient of p_times_q
    # Euler's totient function counts the positive integers up to
    # a given integer **a** that are relatively prime to **a**
    # phi(n) = (p-1) * (q-1)
    phi = (prime_one - 1) * (prime_two - 1)

    # Choose an integer e such that e and phi(p_times_q) are coprime
    e = random.randrange(1, phi+1)

    # phi must not share a factor with e
    # Use Euclid's Algorithm to verify that e and phi(p_times_q) are coprime
    # Two numbers are coprime if the only positive integer (factor) that
    #  divides both of them is 1.
    # Any prime number that divides one does not divide the other.
    # This is equivalent to their greatest common divisor being 1
    # so e * d mod  = 1

    g = gcd(e, phi) # if this returns one, then e is coprime with phi

    while g != 1:
        e = random.randrange(1, phi+1)
        g = gcd(e, phi)
    print e

    # Use Extended Euclid's Algorithm to generate the private key
    # private exponente d, this is used to undo the effect of e
    d = multiplicative_inverse(e, phi)
    # print '(d*e)%phi == ', (d*e)%phi

    # Return public and private keypair
    # Public key is (e, p_times_q) and private key is (d, p_times_q)
    return ((e, p_times_q), (d, p_times_q))

def encrypt(public_key, plaintext):
    # Encrypt: (m^e) % n
    # Unpack the key into it's components
    e, n = public_key
    #Convert each letter in the plaintext to numbers based on the character using a^b mod m
    cipher = [(ord(char) ** e) % n for char in plaintext]
    #Return the array of bytes
    return cipher

def decrypt(private_key, ciphertext):
    # Decrypt: encrypted_c^d % n
    # Unpack the key into its components
    d, n = private_key
    #Generate the plaintext based on the ciphertext and key using a^b mod m
    plain = [chr((char ** d) % n) for char in ciphertext]
    #Return the array of bytes as a string
    return ''.join(plain)

if __name__ == '__main__':
    '''
    Detect if the script is being run directly by the user
    '''
    print "RSA Encrypter/ Decrypter"
    p = int(raw_input("Enter a prime number (17, 19, 23, etc): "))
    q = int(raw_input("Enter another prime number (Not one you entered above): "))
    print "Generating your public/private keypairs now . . ."
    public_key, private_key = generate_keypair(p, q)
    print "Your public key is ", public_key ," and your private key is ", private_key
    message = raw_input("Enter a message to encrypt with your public key: ")
    encrypted_msg = encrypt(public_key, message)
    print "Your encrypted message is: "
    print ''.join(map(lambda x: str(x), encrypted_msg))
    print "Decrypting message with private key ", private_key ," . . ."
    print "Your message is:"
    print decrypt(private_key, encrypted_msg)
