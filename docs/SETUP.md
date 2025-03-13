# Namestitev programske opreme

## Avtomatska namestitev - C, Golang, Julia

---
### Debian, Ubuntu
- Namestitev programskih jezikov Golang, Julia in knjižnice `libjson-c-dev`:
    ```bash
    sudo apt install golang libjson-c-dev
    curl -fsSL https://install.julialang.org | sh
    ```
- Dodajanje poti v PATH v `/~.bashrc`
    ```bash
    source ~/.bashrc
    ```
- Vstop v interaktivni način julia:
    ```bash
    julia
    ```
- Namestitev knjižnic za Julia programski jezik:
    ```julia
    using Pkg
    Pkg.add("ArgParse")
    Pkg.add("JSON")
    ```

---
### Fedora, RHEL, and CentOS
- Namestitev programskega jezika Golang, Julia in knjižnice `json-c-devel`:
    ```bash
    sudo dnf install golang json-c-devel
    curl -fsSL https://install.julialang.org | sh
    ```
- Dodajanje poti v PATH v `/~.bashrc`
    ```bash
    source ~/.bashrc
    ```
- Vstop v interaktivni način julia:
    ```bash
    julia
    ```
- Namestitev knjižnic za Julia programski jezik:
    ```julia
    using Pkg
    Pkg.add("ArgParse")
    Pkg.add("JSON")
    Pkg.add("Dates")
    ```

---
## ? Neuspešna namestitev programskega jezika Julia ?
V primeru, da se julia ne namesti uspešno, lahko sledite navodilom:

1)  Prenos arhiva 
    ```bash
    cd $HOME/Downloads
    wget https://julialang-s3.julialang.org/bin/linux/x64/1.11/julia-1.11.1-linux-x86_64.tar.gz
    ```
2)  Razpakiranje
    ```bash
    tar -xzf julia-1.11.4-linux-x86_64.tar.gz
    ```
3)  Premik razpakirane vsebine v direktorij `/usr/local/julia`
    ```bash
    sudo mv julia-1.11.4 /usr/local/julia
    ```
4)  Dodajanje poti v PATH v `/~.bashrc`
    ```bash
    echo 'export PATH="/usr/local/julia/bin:$PATH"' >> ~/.bashrc
    ```
5) Ponovni zagon terminala ali izvedba
    ```bash
    source ~/.bashrc
    ```
6)  Preverjanje namestitve z
    ```bash
    julia --version
    ```
