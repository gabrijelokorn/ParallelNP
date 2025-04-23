const fs = require('fs').promises;
const { constants } = require('fs');

const languages = ["c", "go", "julia"]
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

async function readThreads(algorithm) {
    let directories = [];
    for (let l of languages) {
        const dirPath = `./${l}/${algorithm}/algo`;
        try {
            const files = await fs.readdir(dirPath, { withFileTypes: true });
            const dirs = files.filter(f => f.isDirectory()).map(f => f.name);
            directories.push(...dirs);
        } catch (err) {
            console.error(`Error reading ${dirPath}:`, err);
        }
    }
    return [...new Set(directories)];
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

async function compare(lang, problemDir, algoName, thread, test, solutionFilename, resultfilename, timefilename) {
    // Create an object for the test
    if (!result[problemDir]) result[problemDir] = {};

    // Create an object for the problem
    if (!result[problemDir][lang]) result[problemDir][lang] = {};

    // Create an object for the language
    if (!result[problemDir][lang][algoName]) result[problemDir][lang][algoName] = {};

    // Create an object for each option of number of threads
    if (!result[problemDir][lang][algoName][test]) result[problemDir][lang][algoName][test] = {};

    // Create an object for the algorithm
    if (!result[problemDir][lang][algoName][test][thread]) result[problemDir][lang][algoName][test][thread] = {
        time: 0,
        correct: false
    };

    if (! await fileExists(resultfilename)) return;

    // Insert the time
    const time = await readCsv(timefilename);
    result[problemDir][lang][algoName][test][thread]["time"] = parseFloat(time.trim());

    if (! await fileExists(solutionFilename)) return;
    // Insert the correct flag
    if (await compareFiles(resultfilename, solutionFilename)) {
        // Read the time.json file
        result[problemDir][lang][algoName][test][thread]["correct"] = true;
    }
}

async function test(partitionTests, kamada_kawaiTests, partitionThreads, kamada_kawaiThreads) {
    // Iterate over all languages
    for (let l of languages) {

        // Iterate over all problems

        // partition
        {
            const problemDir = "partition";
            const algos = await readAlgos(l, problemDir, languageExtensions.get(l));

            for (let thread of partitionThreads) {
                for (let test of partitionTests) {
                    for (let algoName of algos) {
                        const solutionFilename = `../tests/${problemDir}/solutions/${test}.json`;
                        const resultfilename = `${l}/${problemDir}/algo/${thread}/${algoName}${test}.json`;
                        const timefilename = `${l}/${problemDir}/algo/${thread}/${algoName}${test}.txt`;

                        await compare(l, problemDir, algoName, thread, test, solutionFilename, resultfilename, timefilename);
                    }
                }
            }
        }

        // kamada_kawai
        {
            const problemDir = "kamada_kawai";
            const algos = await readAlgos(l, problemDir, languageExtensions.get(l));

            for (let thread of kamada_kawaiThreads) {
                for (let test of kamada_kawaiTests) {
                    for (let algoName of algos) {

                        const solutionFilename = `../tests/${problemDir}/solutions/coords${test}.csv`;
                        const resultfilename = `${l}/${problemDir}/algo/${thread}/${algoName}${test}.csv`;
                        const timefilename = `${l}/${problemDir}/algo/${thread}/${algoName}${test}.txt`;

                        await compare(l, problemDir, algoName, thread, test, solutionFilename, resultfilename, timefilename);
                    }
                }
            }
        }
    }
}

async function evaluateResults(partitionTests, kamada_kawaiTests, partitionThreads, kamada_kawaiThreads) {
    // Iterate over all languages and test cases and define the best time

    {
        const problemDir = "partition";
        for (let x of partitionTests) {
            for (let thread of partitionThreads) {

                let bestTime = Number.MAX_VALUE;
                let worstTime = 0;
                for (let l of languages) {
                    const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                    for (let a of algos) {
                        if (result[problemDir][l][a][x][thread].time > 0) {
                            if (result[problemDir][l][a][x][thread].time < bestTime) {
                                bestTime = result[problemDir][l][a][x][thread].time;
                            }
                            if (result[problemDir][l][a][x][thread].time > worstTime) {
                                worstTime = result[problemDir][l][a][x][thread].time;
                            }
                        }
                    }

                }
                // normalize and give each algorithm a score based on the best time (the fastest algorithm gets 1 and the rest get a score between 0 and 1)
                for (let l of languages) {
                    const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                    for (let a of algos) {
                        if (result[problemDir][l][a][x][thread].time === 0) {
                            continue;
                        }
                        if (bestTime === result[problemDir][l][a][x][thread].time) {
                            result[problemDir][l][a][x][thread]["score"] = 1;
                            continue;
                        }
                        if (worstTime === result[problemDir][l][a][x][thread].time) {
                            result[problemDir][l][a][x][thread]["score"] = 0;
                            continue;
                        }
                        result[problemDir][l][a][x][thread]["score"] = (worstTime - result[problemDir][l][a][x][thread].time) / (worstTime - bestTime);
                    }
                }
            }
        }
    }

    {
        const problemDir = "kamada_kawai";
        for (let x of kamada_kawaiTests) {
        for (let thread of kamada_kawaiThreads) {
            let bestTime = Number.MAX_VALUE;
            let worstTime = 0;
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x][thread].time > 0) {
                        if (result[problemDir][l][a][x][thread].time < bestTime) {
                            bestTime = result[problemDir][l][a][x][thread].time;
                        }
                        if (result[problemDir][l][a][x][thread].time > worstTime) {
                            worstTime = result[problemDir][l][a][x][thread].time;
                        }
                    }
                }

            }
            // normalize and give each algorithm a score based on the best time (the fastest algorithm gets 1 and the rest get a score between 0 and 1)
            for (let l of languages) {
                const algos = await readAlgos(l, problemDir, languageExtensions.get(l));
                for (let a of algos) {
                    if (result[problemDir][l][a][x][thread].time === 0) {
                        continue;
                    }
                    if (bestTime === result[problemDir][l][a][x][thread].time) {
                        result[problemDir][l][a][x][thread]["score"] = 1;
                        continue;
                    }
                    if (worstTime === result[problemDir][l][a][x][thread].time) {
                        result[problemDir][l][a][x][thread]["score"] = 0;
                        continue;
                    }
                    result[problemDir][l][a][x][thread]["score"] = (worstTime - result[problemDir][l][a][x][thread].time) / (worstTime - bestTime);
                }
            }
        }
        }
    }
}

async function main() {
    // Read the names of the tests
    const one_partition = "partition";
    const one_kamada_kawai = "kamada_kawai";
    const partitionTests = await readTests(one_partition);
    const kamada_kawaiTests = await readTests(one_kamada_kawai);

    const partitionThreads = await readThreads(one_partition);
    const kamada_kawaiThreads = await readThreads(one_kamada_kawai);

    // Run the tests
    await test(partitionTests, kamada_kawaiTests, partitionThreads, kamada_kawaiThreads);

    // Evaluate the results
    await evaluateResults(partitionTests, kamada_kawaiTests, partitionThreads, kamada_kawaiThreads);

    // Create the checks.js file
    const output = `const results = ${JSON.stringify(result)};`;

    const partitionTestsString = `const partitionTests = ${JSON.stringify(partitionTests)};`;
    const kamada_kawaiTestsString = `const kamada_kawaiTests = ${JSON.stringify(kamada_kawaiTests)};`;
    const partitionThreadsString = `const partitionThreads = ${JSON.stringify(partitionThreads)};`;
    const kamada_kawaiThreadsString = `const kamada_kawaiThreads = ${JSON.stringify(kamada_kawaiThreads)};`;

    await fs.writeFile('../views/assets/checks.js', output);
    await fs.appendFile('../views/assets/checks.js', partitionTestsString);
    await fs.appendFile('../views/assets/checks.js', kamada_kawaiTestsString);
    await fs.appendFile('../views/assets/checks.js', partitionThreadsString);
    await fs.appendFile('../views/assets/checks.js', kamada_kawaiThreadsString);
}

main();