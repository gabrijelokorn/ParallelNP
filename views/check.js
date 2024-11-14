const fs = require('fs').promises;
const { constants } = require('fs');
const { parse } = require('csv-parse');

const languages = ["c", "julia", "golang"];
const programTypes = ["s", "p"];

const result = {
    c: {
        s: {

            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
        },
        p: {
            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
        }
    },
    julia: {
        s: {
            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
        },
        p: {
            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
        }
    },
    golang: {
        s: {
            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
        },
        p: {
            big_partition: {},
            small_partitions: {},
            kamada_kawai: {}
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
    return fs.readdir(`tests/${algorithm}`)
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

async function compare(l, t, a, n, filename, solutionFilename) {
    if (! await fileExists(filename) || ! await fileExists(solutionFilename)) return;

    if (await compareFiles(filename, solutionFilename)) result[l][t][a][n] = true;
    else result[l][t][a][n] = false;
}

async function iterate(big_partitionTests, small_partitionsTests, kamada_kawaiTests) {
    // Iterate over all languages
    for (let l of languages) {
        // For both program types
        for (let t of programTypes) {
            // Iterate over all algorithms

            // big_partition
            for (let test of big_partitionTests) {
                const a = "big_partition";

                const solutionFilename = `tests/${a}/solutions/${test}.json`;
                const filename = `${l}/${a}/${t}${test}.json`;

                await compare(l, t, a, test, filename, solutionFilename);
            }

            // small_partitions
            for (let test of small_partitionsTests) {
                const a = "small_partitions";

                const solutionFilename = `tests/${a}/solutions/${test}.json`;
                const filename = `${l}/${a}/${t}${test}.json`;

                await compare(l, t, a, test, filename, solutionFilename);
            }

            // kamada_kawai
            for (let test of kamada_kawaiTests) {
                const a = "kamada_kawai";

                const solutionFilename = `tests/${a}/solutions/coords${test}.csv`;
                const filename = `${l}/${a}/${t}${test}.csv`;

                await compare(l, t, a, test, filename, solutionFilename);
            }
        }
    }
}


async function test() {
    const big_partitionTests = await readTests("big_partition");
    const small_partitionsTests = await readTests("small_partitions");
    const kamada_kawaiTests = await readTests("kamada_kawai");

    await iterate(big_partitionTests, small_partitionsTests, kamada_kawaiTests);

    const output = `const results = ${JSON.stringify(result)};`;
    fs.writeFile('views/checks.js', output);
}

test();