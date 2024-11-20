
# Zahtevana programska oprema

## Debian, Ubuntu

### Pregled potrebne programske opreme
| - | C | Go | Julia |
|---|---|----|-------|
| **Avtomatska namestitev** | - | `sudo apt install golang` | curl -fsSL https://install.julialang.org | sh |
| **Ročna namestitev** | - | - | <ol><li>Prenos arhiva</li><li>Razpakiranje</li><li>Premik v direktorij `/usr/local/julia`</li><li>Dodajanje poti v `PATH` v `/~.bashrc`</li></ol> |
| **Knjižnice** | `sudo apt install libjson-c-dev` | - | <ol><li>```julia```</li><li>```using Pkg```</li><li>```Pkg.add("PackageName")```</li></ol> |

### Namestitev programske opreme
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

## Fedora, RHEL, and CentOS

### Pregled potrebne programske opreme
| - | C | Go | Julia |
|---|---|----|-------|
| **Avtomatska namestitev** | - | `sudo dnf install golang` | curl -fsSL https://install.julialang.org | sh |
| **Ročna namestitev** | - | - | <ol><li>Prenos arhiva</li><li>Razpakiranje</li><li>Premik v direktorij `/usr/local/julia`</li><li>Dodajanje poti v `PATH` v `/~.bashrc`</li></ol> |
| **Knjižnice** | `sudo dnf install json-c-devel` | - | <ol><li>```julia```</li><li>```using Pkg```</li><li>```Pkg.add("PackageName")```</li></ol> |

### Namestitev programske opreme
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
