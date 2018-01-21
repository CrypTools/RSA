# RSA

# Detailed Explanations : How it works?
RSA works using a public key and a private key and it's strength relies on the hardness of prime factorization (a set of prime numbers that you multiply together to get another number). The first step in the RSA algorithm involves generating the keys.
## Generating key
This is done in generate_keypair(private_key, public_key) function.
Before we call this function we choose two different prime numbers (p and q), one for our private key and the other for our public key. Lets imagine I pick **2** and **7**, and then we pass it to our function, so:
```
p = 2
q = 7
public_key, private_key = generate_keypair(2, 7)
```
## Encryption
φ
