const fs = require('fs').promises;
const { constants } = require('fs');
const { parse } = require('csv-parse');

const languages = ["c", "julia", "go"];
const programTypes = ["s", "p"];

const result = {
    c: {
        s: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        },
        p: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        }
    },
    julia: {
        s: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        },
        p: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        }
    },
    go: {
        s: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        },
        p: {
            partition: {
                l: {},
                s: {}
            },
            kamada_kawai: {
                n: {}
            }
        }
    }
};

async function readJson(filename) {
    return fs.readFile(filename, 'utf8')
        .then(data => JSON.parse(data))
        .catch(err => {
            return false;
        });
}

async function readCsv(filename) {
    return fs.readFile(filename, 'utf8')
        .then(data => {
            return data;
        })
        .catch(err => {
            console.log("Error reading csv", err);
        });
}

async function fileExists(filepath) {
    try {
        await fs.access(filepath, constants.F_OK);
        return true;
    } catch (error) {
        return false;
    }
}

async function compareFiles(file1, file2) {
    const ext = file1.split('.').pop();
    try {
        const data1 = ext === 'json' ? await readJson(file1) : await readCsv(file1);
        const data2 = ext === 'json' ? await readJson(file2) : await readCsv(file2);

        if (data1 && data2) {
            return JSON.stringify(data1) === JSON.stringify(data2);
        }
    } catch (err) {
        console.error("Error comparing files", err);
    }

}

function readTests(algorithm) {
    return fs.readdir(`../tests/${algorithm}`)
        .then(files => {
            const prefixes = files.filter(file => file.endsWith(".json"));
            const filenames = prefixes.map(file => {
                return file.split(".")[0];
            });

            return filenames;
        })
        .catch(err => {
            console.error("Error reading tests", err);
        });
}

async function compare(l, t, a, sa, n, filename, solutionFilename) {
    if (! await fileExists(filename) || ! await fileExists(solutionFilename)) return;

    if (await compareFiles(filename, solutionFilename)) result[l][t][a][sa][n] = true;
    else result[l][t][a][sa][n] = false;
}

async function iterate(l_partitionTests, s_partitionTests, kamada_kawaiTests) {
    // Iterate over all languages
    for (let l of languages) {
        // For both program types
        for (let t of programTypes) {
            // Iterate over all algorithms

            // l_partition
            for (let test of l_partitionTests) {
                const algoDir = "partition/l";
                const algoName = "partition";
                const subAlgo = "l"
                
                const solutionFilename = `../tests/${algoDir}/solutions/${test}.json`;
                const filename = `${l}/${algoDir}/${t}${test}.json`;
                
                await compare(l, t, algoName, subAlgo, test, filename, solutionFilename);
            }
            
            // s_partition
            for (let test of s_partitionTests) {
                const algoDir = "partition/s";
                const algoName = "partition";
                const subAlgo = "s";
                
                const solutionFilename = `../tests/${algoDir}/solutions/${test}.json`;
                const filename = `${l}/${algoDir}/${t}${test}.json`;
                
                await compare(l, t, algoName, subAlgo, test, filename, solutionFilename);
            }
            
            // kamada_kawai
            for (let test of kamada_kawaiTests) {
                const algoDir = "kamada_kawai";
                const algoName = "kamada_kawai";
                const subAlgo = "n";

                const solutionFilename = `../tests/${algoDir}/solutions/coords${test}.csv`;
                const filename = `${l}/${algoDir}/${t}${test}.csv`;

                await compare(l, t, algoName, subAlgo, test, filename, solutionFilename);
            }
        }
    }
}


async function test() {
    const l_partitionTests = await readTests("partition/l");
    const s_partitionTests = await readTests("partition/s");
    const kamada_kawaiTests = await readTests("kamada_kawai");

    await iterate(l_partitionTests, s_partitionTests, kamada_kawaiTests);

    const output = `const results = ${JSON.stringify(result)};`;
    fs.writeFile('../views/assets/checks.js', output);
}

test();