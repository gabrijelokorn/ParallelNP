# Namestitev programske opreme

## Avtomatska namestitev

### Debian, Ubuntu
```bash
sudo apt install golang libjson-c-dev
curl -fsSL https://install.julialang.org | sh
```
```bash
source ~/.bashrc
```
```bash
julia
```
```julia
using Pkg
Pkg.add("ArgParse")
```

### Fedora, RHEL, and CentOS
```bash
sudo dnf install golang json-c-devel
curl -fsSL https://install.julialang.org | sh
```
```bash
source ~/.bashrc
```
```bash
julia
```
```julia
using Pkg
Pkg.add("ArgParse")
```

## Ročna namestitev
V primeru, da se julia ne namesti pravilno, lahko sledite navodilom:

1)  Prenos arhiva
2)  Razpakiranje
3)  Premik razpakirane vsebine v direktorij `/usr/local/julia`
4)  Dodajanje poti v PATH v `/~.bashrc`
5) `source ~/.bashrc`
6)  Preverjanje namestitve z `julia --version`
