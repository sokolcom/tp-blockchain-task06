# TP BLOCKCHAIN TASK #06
# Shamir's Secret Sharing



### What is it? 👀


This program shares 256 bit key (e.g. ECDSA secp256k1 private key) between ___N___ members using [Shamir's Secret Sharing](https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing) and recovers secret by any ___T___ (or more) shares.


### USAGE 🌍

1. ⭐ Star this repo.
2. 📂 Clone this repo (e.g. via ```git clone```).
```sh
git clone https://github.com/sokolcom/tp-blockchain-task06.git
```
3. 🔨 Run ```make``` in the repo directory to build the program (```app.out```).
```sh
make
```
4. 🚀 To run program simply execute:
```sh
/app.out <mode>
```
where
* \<mode\>: program mode ("__split__" or "__recover__").

5. 🔍 You can run ```make split``` or ```make recover```, which ivokes 
```sh
/app.out split
 ```
 and 
 ```sh
/app.out recover
 ```

### Examples :telescope:
* SECRET: `0xF1`, N: 3, T: 2
![0xf1](/images/0xf1.png)
* SECRET: `0xDEADBEEF`, N: 5, T: 3
![0xf1](/images/0xdeadbeef.png)




