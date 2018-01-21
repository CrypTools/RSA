# RSA (Rivest–Shamir–Adleman)

# Detailed Explanations : How it works?
RSA works using a **public key** and a **private key** and it's strength relies on the hardness of **prime factorization** (a set of prime numbers that you multiply together to get another number). The first step in the RSA algorithm involves generating the keys.
## Generating key
### Choosing two primes
This is done in generate_keypair(private_key, public_key) function.
Before we call this function we choose two different prime numbers (p and q), one for our private key and the other for our public key. Lets imagine I pick **2** and **7**, and **then we pass it to our function**, so:
```
p = 17
q = 19
105     public_key, private_key = generate_keypair(17, 19)
```
### Calculating **n**
Now the first thing we do inside this function is to compute **n** and it's nothing more than **p** and **q** multiplied together. **n** is used as the modulus for the encrypting key and decryption key. So let't calculate our **n**:
```
61      # n = prime_one * prime_two
62      p_times_q = prime_one * prime_two #n
62      p_times_q = 17 * 19 # 323
```
### Using Euler's totient function to calculate **Phi** (φ)
Next comes calculating **Phi(n) (φ(n))** and it's used to calculate how many integers are less than or equal to **n** that **do not** share any common factor with **n**. What's interesting and important here, is that, calculating the **phi** function is hard, except in the case of **prime numbers**. Since prime numbers have no factors greater than one, the **phi** of any prime number, **p** is simply **p - 1**. Therefore:
```
# n = p * q
# φ(n) = φ(p) * φ(q)
```
In our code:
```
68      phi = (prime_one - 1) * (prime_two - 1)
68      phi = (17 -1) * (19 -1) # 288 is the number of integers that are coprime with 323
```
### Choosing **e**
**e** is important for our encryption because **e** and **n** it will become our **public_key**. **e** must be picked randomly and have certain properties. Such as:
- 1 < **e** < φ(n) (in our case **e** must be between 1 and 288)
- Must be coprime with **n** and φ(n) (in our case, must be coprime with 323 and 288)
We do so here:
```
75      e = random.randrange(1, phi+1)
86      g = gcd(e, phi) # if this returns one, then e is coprime with phi
```
if **g** returns one then **e** is **coprime** with **phi**, so their greatest common divisor is **1**, which means that **1** is the only positive integer (factor) that divides both of them, **e** and **phi**.

### Calculating **d**
We use the Extended Euclid's Algorithm to generate **d**. This is a private exponent, it will be a part of our **private key** and this is used to undo the effect of **e**
```
98      d = multiplicative_inverse(e, phi)
```
### Public key and Private key
With **n**, **e** and **d**, we can now get our **public** and **private** key pairs.

```
104     return ((e, p_times_q), (d, p_times_q))
```
## Public key
The **public key pair** is (**e**, **n**). This is what the server sends us, its public and anyone can read it.
## Private key
The **private key pair** is (**d**, **n**). This can not be shared with anyone. It will be used to decrypt messages encrypted with the public key.


### Encrypting
For encrypting this is what we do:
``` (m^e) % n```
This function will use the public key to encrypt our plain text. We'll encrypt the string "asd".
Let's first get our **e** and **n** from our **public key** pair. Then, we loop through each character in our string and get the Unicode value using **ord()** function. With this we then exponentiate that value by **e** and finally get the remainder with **mod n**.
```
111     e, n = public_key
129     plain = [(char ** d) % n for char in ciphertext]
```
Our encrypted message should look like this:
```
147191111
```

### Decrypting
In the **decrypting** process we use our **private key**, and the process in almost the same, except that, we use **d** our private exponent instead of **e**. So:
```
(encrypted_character^d) % n
```
Now we loop through each character performing our calculation. In the end we use **chr()** function to get our character back.
```
113     d, n = private_key
115     plain = [chr((char ** d) % n) for char in ciphertext]
```
