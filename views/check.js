const fs = require('fs').promises;
const { constants } = require('fs');
const {parse} = require('csv-parse');

const languages = ["c", "julia", "golang"];
const programType = ["sequential", "parallel"];
const algorithms = ["big_partition", "small_partitions", "Kamada_Kawai"];

const results = {
    big_partition: {},
    small_partitions: {},
    Kamada_Kawai: {},
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

async function compare(big_partitionTests, small_partitionsTests, Kamada_KawaiTests) {
    // Iterate over all algorithms
    for (let a of algorithms) {
        if (a === "big_partition") {

            // Iterate over all tests for the algorithm
            for (let test of big_partitionTests) {
                // Check if the solution file exists
                if (await fileExists(`tests/${a}/solutions/${test}.json`)) {

                    // Create an array to store the paths of the output files that match the solution
                    results[a][test] = {};

                    // Iterate over all languages
                    for (let l of languages) {
                        results[a][test][l] = {};
                        // Iterate over all program types
                        for (let p of programType) {

                            const filename = `${l}/${p}/${a}/output${test}.json`;
                            if (await fileExists(filename)) {
                                if (await (compareFiles(filename, `tests/${a}/solutions/${test}.json`))) {
                                    results[a][test][l][p] = true;
                                } else {
                                    results[a][test][l][p] = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (a === "small_partitions") {

            // Iterate over all tests for the algorithm
            for (let test of small_partitionsTests) {
                // Check if the solution file exists
                if (await fileExists(`tests/${a}/solutions/${test}.json`)) {

                    // Create an array to store the paths of the output files that match the solution
                    results[a][test] = {};

                    // Iterate over all languages
                    for (let l of languages) {
                        results[a][test][l] = {};
                        // Iterate over all program types
                        for (let p of programType) {

                            const filename = `${l}/${p}/${a}/output${test}.json`;
                            if (await fileExists(filename)) {
                                if (await (compareFiles(filename, `tests/${a}/solutions/${test}.json`))) {
                                    results[a][test][l][p] = true;
                                } else {
                                    results[a][test][l][p] = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (a === "Kamada_Kawai") {
            for (let test of Kamada_KawaiTests) {
                if (await fileExists(`tests/${a}/solutions/coords${test}.csv`)) {

                    // Create an array to store the paths of the output files that match the solution
                    results[a][test] = {};

                    // Iterate over all languages
                    for (let l of languages) {
                        results[a][test][l] = {};
                        // Iterate over all program types
                        for (let p of programType) {

                            const filename = `${l}/${p}/${a}/coords${test}.csv`;

                            if (await fileExists(filename)) {
                                if (await (compareFiles(filename, `tests/${a}/solutions/coords${test}.csv`))) {
                                    results[a][test][l][p] = true;
                                } else {
                                    results[a][test][l][p] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

async function test() {
    const big_partitionTests = await readTests("big_partition");
    const small_partitionsTests = await readTests("small_partitions");
    const Kamada_KawaiTests = await readTests("Kamada_Kawai");

    await compare(big_partitionTests, small_partitionsTests, Kamada_KawaiTests);

    const output = `const results = ${JSON.stringify(results)};`;
    fs.writeFile('views/checks.js', output);
}

test();