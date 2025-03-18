const fs = require('fs').promises;
const { constants } = require('fs');

const languages = ["c", "julia", "go"]
const languageExtensions = new Map([
    ["c", ".c"],
    ["julia", ".jl"],
    ["go", ".go"]
]);
const filesToIgnore = [
    "algo",
    "kamada_kawai",
    "kamada_kawai2csv"
]

const result = {
};


async function readAlgos(lang, algo, postfix) {
    return fs.readdir(`./${lang}/${algo}/algo`)
        .then(files => {
            const prefixes = files
                .filter(file => file.endsWith(postfix))
                .filter(file => !filesToIgnore.includes(file.split(".")[0]));
            const filenames = prefixes.map(file => {
                return file.split(".")[0];
            });

            return filenames;
        })
        .catch(err => {
            console.error("Error reading tests", err);
        });
}

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

async function compare(lang, problemDir, algoName, test, solutionFilename, resultfilename, timefilename) {
    // Create an object for the test
    if (!result[problemDir]) result[problemDir] = {};

    // Create an object for the problem
    if (!result[problemDir][lang]) result[problemDir][lang] = {};

    // Create an object for the language
    if (!result[problemDir][lang][algoName]) result[problemDir][lang][algoName] = {};

    // Create an object for the algorithm
    if (!result[problemDir][lang][algoName][test]) result[problemDir][lang][algoName][test] = {
        time: 0,
        correct: false
    };

    if (! await fileExists(resultfilename)) return;

    // Insert the time
    const time = await readCsv(timefilename);
    result[problemDir][lang][algoName][test]["time"] = time;

    if (! await fileExists(solutionFilename)) return;
    // Insert the correct flag
    if (await compareFiles(resultfilename, solutionFilename)) {
        // Read the time.json file
        result[problemDir][lang][algoName][test]["correct"] = true;
    }
}

async function test(partitionTests, kamada_kawaiTests) {
    // Iterate over all languages
    for (let l of languages) {

        // Iterate over all problems

        // partition
        {
            const problemDir = "partition";
            const algos = await readAlgos(l, problemDir, languageExtensions.get(l));

            for (let test of partitionTests) {
                for (let algoName of algos) {
                    const solutionFilename = `../tests/${problemDir}/solutions/${test}.json`;
                    const resultfilename = `${l}/${problemDir}/algo/${algoName}${test}.json`;
                    const timefilename = `${l}/${problemDir}/algo/${algoName}${test}.txt`;

                    await compare(l, problemDir, algoName, test, solutionFilename, resultfilename, timefilename);
                }
            }
        }

        // kamada_kawai
        {
            const problemDir = "kamada_kawai";
            const algos = await readAlgos(l, problemDir, languageExtensions.get(l));

            for (let test of kamada_kawaiTests) {
                for (let algoName of algos) {

                    const solutionFilename = `../tests/${problemDir}/solutions/coords${test}.csv`;
                    const resultfilename = `${l}/${problemDir}/algo/${algoName}${test}.csv`;
                    const timefilename = `${l}/${problemDir}/algo/${algoName}${test}.txt`;

                    await compare(l, problemDir, algoName, test, solutionFilename, resultfilename, timefilename);
                }
            }
        }
    }
}

async function evaluateResults(partitionTests, kamada_kawaiTests) {
    // Iterate over all languages and test cases and define the best time

    {
        const problemDir = "partition";
        for (let x of partitionTests) {
            let bestTime = Number.MAX_VALUE;
            let worstTime = 0;
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x].time > 0) {
                        if (result[problemDir][l][a][x].time < bestTime) {
                            bestTime = result[problemDir][l][a][x].time;
                        }
                        if (result[problemDir][l][a][x].time > worstTime) {
                            worstTime = result[problemDir][l][a][x].time;
                        }
                    }
                }

            }
            // normalize and give each algorithm a score based on the best time (the fastest algorithm gets 1 and the rest get a score between 0 and 1)
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x].time === 0) {
                        continue;
                    }
                    if (bestTime === result[problemDir][l][a][x].time) {
                        result[problemDir][l][a][x]["score"] = 1;
                        continue;
                    }
                    if (worstTime === result[problemDir][l][a][x].time) {
                        result[problemDir][l][a][x]["score"] = 0;
                        continue;
                    }
                    result[problemDir][l][a][x]["score"] = (worstTime - result[problemDir][l][a][x].time) / (worstTime - bestTime);
                }
            }
        }
    }

    {
        const problemDir = "kamada_kawai";
        for (let x of kamada_kawaiTests) {
            let bestTime = Number.MAX_VALUE;
            let worstTime = 0;
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x].time > 0) {
                        if (result[problemDir][l][a][x].time < bestTime) {
                            bestTime = result[problemDir][l][a][x].time;
                        }
                        if (result[problemDir][l][a][x].time > worstTime) {
                            worstTime = result[problemDir][l][a][x].time;
                        }
                    }
                }

            }
            // normalize and give each algorithm a score based on the best time (the fastest algorithm gets 1 and the rest get a score between 0 and 1)
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x].time === 0) {
                        continue;
                    }
                    if (bestTime === result[problemDir][l][a][x].time) {
                        result[problemDir][l][a][x]["score"] = 1;
                        continue;
                    }
                    if (worstTime === result[problemDir][l][a][x].time) {
                        result[problemDir][l][a][x]["score"] = 0;
                        continue;
                    }
                    result[problemDir][l][a][x]["score"] = (worstTime - result[problemDir][l][a][x].time) / (worstTime - bestTime);
                }
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

    // Evaluate the results
    await evaluateResults(partitionTests, kamada_kawaiTests);

    // Create the checks.js file
    const output = `const results = ${JSON.stringify(result)};`;

    const partitionTestsString = `const partition = ${JSON.stringify(partitionTests)};`;
    const kamada_kawaiTestsString = `const kamada_kawai = ${JSON.stringify(kamada_kawaiTests)};`;

    await fs.writeFile('../views/assets/checks.js', output);
    await fs.appendFile('../views/assets/checks.js', partitionTestsString);
    await fs.appendFile('../views/assets/checks.js', kamada_kawaiTestsString);
}

main();