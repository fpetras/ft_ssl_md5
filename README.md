# ft_ssl_md5

An introduction to cryptographic hashing algorithms

This project consists of recoded versions of the message-digest algorithm MD5 and the entire SHA-2 family of hash functions.

Built from the ground up using only these functions:

* open, close
* read, write
* malloc, free
* strerror, exit

## Installation:

`git clone https://github.com/fpetras/ft_ssl_md5.git && cd ft_ssl_md5 && make`

## Command-line completion

ft_ssl features tab completion for Zsh.

To enable, move `_ft_ssl` into a directory included in `$fpath`, and restart your terminal session.

## Usage:

```
usage: ./ft_ssl <command> [-pqr] [-s <string>] [<file>...]

COMMANDS
     md5
     sha224 sha256 sha384 sha512 sha512224 sha512256

OPTIONS
     -p            echo stdin to stdout and append checksum to stdout
     -q            quiet mode
     -r            reverse the format of the output
     -s <string>   print the sum of the given string
```

## Examples:

Mimics the behaviour of the `md5` utility:

```
echo -n "hello world" | ./ft_ssl md5
5eb63bbbe01eeed093cb22bb8f5acdc3
```

```
echo "MD5 was designed by Ronald Rivest in 1991" | ./ft_ssl md5 -p
MD5 was designed by Ronald Rivest in 1991
b10422a016cb412cc9d432ff3c05e238
```

```
./ft_ssl md5 main.c
MD5 (main.c) = 5c9752527df82f35affe6f423fd48a15
```

```
./ft_ssl md5 -rs "abcdefghijklmnopqrstuvwxyz"
c3fcd3d76192e4007dfb496cca67e13b "abcdefghijklmnopqrstuvwxyz"
```

Works with binary files:

```
cat ft_ssl | ./ft_ssl sha256
ce9e249b1dc3c8fc9b7d63ba777eb290f9284309cc9f71104b7ba2e4292c61e4
```

Empty string hash values:

```
./ft_ssl md5 -qs ""
d41d8cd98f00b204e9800998ecf8427e
```

```
./ft_ssl sha224 -qs ""
d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f

./ft_ssl sha256 -qs ""
e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

./ft_ssl sha384 -qs ""
38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b

./ft_ssl sha512 -qs ""
cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e

./ft_ssl sha512224 -qs ""
6ed0dd02806fa89e25de060c19d3ac86cabb87d6a0ddd05c333b84f4

./ft_ssl sha512256 -qs ""
c672b8d1ef56ed28ab87c3622c5114069bdd3ad7b8f9737498d0c01ecef0967a
```

### Test script:

Test the hash functions by running

`./test.sh <command>...`

or

`make test[_<command>]`

![sha256_test_gif](http://g.recordit.co/YUL0DdvJ3z.gif)

## FAQ:

**Q:** Why is the code structured so strangely?

**A:** It follows the set of rules described in this document: [Norm](https://github.com/fpetras/42-documents/blob/master/norm.en.pdf "norm.en.pdf")

**Q:** How do the hash algorithms work?

**A:** Refer to Wikipedia to get a quick overview:

https://en.wikipedia.org/wiki/MD5

https://en.wikipedia.org/wiki/SHA-2

On top of that, these documents provide an excellent in-depth description of the SHA-2 algorithms:

http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf

https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

## Code snippets:

SHA-256 hash computation:

``` C
static void     operations(uint32_t *vars, uint32_t *w, size_t i)
{
    uint32_t ch;
    uint32_t maj;
    uint32_t s[2];
    uint32_t tmp[2];

    ch = (vars[E] & vars[F]) ^ ((~vars[E]) & vars[G]);
    maj = (vars[A] & vars[B]) ^ (vars[A] & vars[C]) ^ (vars[B] & vars[C]);
    s[0] = rightrotate(vars[A], 2) ^ rightrotate(vars[A], 13) ^
    rightrotate(vars[A], 22);
    s[1] = rightrotate(vars[E], 6) ^ rightrotate(vars[E], 11) ^
    rightrotate(vars[E], 25);
    tmp[0] = vars[I] + s[1] + ch + g_k[i] + w[i];
    tmp[1] = s[0] + maj;
    vars[I] = vars[G];
    vars[G] = vars[F];
    vars[F] = vars[E];
    vars[E] = vars[D] + tmp[0];
    vars[D] = vars[C];
    vars[C] = vars[B];
    vars[B] = vars[A];
    vars[A] = tmp[0] + tmp[1];
}
```

Printing of the final SHA-512 hash:

``` C
ft_printf("%016llx%016llx%016llx%016llx%016llx%016llx%016llx%016llx",
hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7]);
```

## [Subject](https://github.com/fpetras/42-subjects/blob/master/ft_ssl_md5.en.pdf "ft_ssl_md5.en.pdf")
