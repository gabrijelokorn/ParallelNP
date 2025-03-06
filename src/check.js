const fs = require('fs').promises;
const { constants } = require('fs');
const { parse } = require('csv-parse');

const languages = ["c", "julia", "go"];
const programTypes = ["s", "p"];

const result = {
    c: {
        partition: {
            l: {},
            s: {}
        },
        kamada_kawai: {
            n: {}
        }
    },
    julia: {
        partition: {
            l: {},
            s: {}
        },
        kamada_kawai: {
            n: {}
        }
    },
    go: {
        partition: {
            l: {},
            s: {}
        },
        kamada_kawai: {
            n: {}
        }
    }
};


async function readTests(algorithm) {
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

async function fileExists(filepath) {
    try {
        await fs.access(filepath, constants.F_OK);
        return true;
    } catch (error) {
        return false;
    }
}

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

async function compare(l, t, a, sa, n, filename, solutionFilename, timefilename) {
    if (! await fileExists(filename) || ! await fileExists(solutionFilename)) return;

    if (!result[l][a][sa][n]) result[l][a][sa][n] = {};
    result[l][a][sa][n][t] = {
        time: 0,
        correct: false
    };

    const time = await readCsv(timefilename);
    result[l][a][sa][n][t]["time"] = time;

    if (await compareFiles(filename, solutionFilename)) {
        // Read the time.json file
        result[l][a][sa][n][t]["correct"] = true;
    }
}

async function test(partitionTests, kamada_kawaiTests) {
    // Iterate over all languages
    for (let l of languages) {
        // For both program types
        for (let t of programTypes) {
            // Iterate over all algorithms

            // partition
            for (let test of partitionTests) {
                const algoDir = "partition";
                const algoName = "partition";
                const subAlgo = "l"

                // const solutionFilename = `../tests/${algoDir}/solutions/${test}.json`;
                // const testfilename = `${l}/${algoDir}/${t}${test}.json`;
                // const timefilename = `${l}/${algoDir}/${t}${test}t.txt`;

                // await compare(l, t, algoName, subAlgo, test, testfilename, solutionFilename, timefilename);
            }

            // kamada_kawai
            for (let test of kamada_kawaiTests) {
                const algoDir = "kamada_kawai";
                const algoName = "kamada_kawai";
                const subAlgo = "n";

                // const solutionFilename = `../tests/${algoDir}/solutions/coords${test}.csv`;
                // const testfilename = `${l}/${algoDir}/${t}${test}.csv`;
                // const timefilename = `${l}/${algoDir}/${t}${test}t.txt`;

                // await compare(l, t, algoName, subAlgo, test, testfilename, solutionFilename, timefilename);
            }
        }
    }
}

async function main() {
    // Read the names of the tests
    const partitionTests = await readTests("partition");
    const kamada_kawaiTests = await readTests("kamada_kawai");

    // Run the tests
    await test(partitionTests, kamada_kawaiTests);

    // Create the checks.js file
    const output = `const results = ${JSON.stringify(result)};`;
    fs.writeFile('../views/assets/checks.js', output);
}

main();