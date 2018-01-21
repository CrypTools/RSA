# RSA (Rivest–Shamir–Adleman)

# Detailed Explanations : How it works?
RSA works using a **public key** and a **private key** and it's strength relies on the hardness of **prime factorization** (a set of prime numbers that you multiply together to get another number). The first step in the RSA algorithm involves generating the keys.
## Generating key
### Choosing two primes
This is done in generate_keypair(private_key, public_key) function.
Before we call this function we choose two different prime numbers (p and q), one for our private key and the other for our public key. Lets imagine I pick **2** and **7**, and **then we pass it to our function**, so:
```
p = 2
q = 7
105     public_key, private_key = generate_keypair(2, 7)
```
### Calculating **n**
Now the first thing we do inside this function is to compute **n** and it's nothing more than **p** and **q** multiplied together. **n** is used as the modulus for the encrypting key and decryption key. So let't calculate our **n**:
```
61      # n = prime_one * prime_two
62      p_times_q = prime_one * prime_two #n
62      p_times_q = 2 * 7 # 14
```
### Using Euler's totient function to calculate **Phi** (φ)
Next comes calculating **Phi(n) (φ(n))** and it's used to calculate how many integers are less than or equal to **n** that **do not** share any common factor with **n**. What's interesting and important here, is that, calculating the **phi** function is hard, except in the case of **prime numbers**. Since prime numbers have no factors greater than one, the **phi** of any prime number, **p** is simply **p - 1**. Therefore:
```
# n = p * q
# φ(n) = φ(p) * φ(q)
```
```
68      phi = (prime_one - 1) * (prime_two - 1)
68      phi = (2 -1) * (7 -1) # 6 is the number of integers that are coprime with 14
```
### Choose **e**









## Encryption
