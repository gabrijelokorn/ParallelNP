const fs = require('fs').promises;
const { constants } = require('fs');
const { parse } = require('csv-parse');

const languages = ["c"]
// const languages = ["c", "julia", "go"];

const result = {
    c: {
        partition: {
        },
        kamada_kawai: {
        }
    },
    julia: {
        partition: {
        },
        kamada_kawai: {
        }
    },
    go: {
        partition: {
        },
        kamada_kawai: {
        }
    }
};


async function readAlgos(lang, algo, postfix) {
    return fs.readdir(`./${lang}/${algo}/algo`)
        .then(files => {
            const prefixes = files.filter(file => file.endsWith(postfix)).filter(file => !file.startsWith("algo"));
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
    // Create an object for the algorithm
    if (!result[lang][problemDir][test]) result[lang][problemDir][test] = {};
    
    // Create an object for the test
    if (!result[lang][problemDir][test][algoName]) result[lang][problemDir][test][algoName] = {};
    result[lang][problemDir][test][algoName] = {
        time: 0,
        correct: false
    };
    
    if (! await fileExists(resultfilename) || ! await fileExists(solutionFilename)) return;
    
    // Insert the time
    const time = await readCsv(timefilename);
    result[lang][problemDir][test][algoName]["time"] = time;

    // Insert the correct flag
    if (await compareFiles(resultfilename, solutionFilename)) {
        // Read the time.json file
        result[lang][problemDir][test][algoName]["correct"] = true;
    }
}

async function test(partitionTests, kamada_kawaiTests) {
    // Iterate over all languages
    for (let l of languages) {
        // Iterate over all problems

        // partition
        {
            const problemDir = "partition";
            const algos = await readAlgos(l, problemDir, `.${l}`);

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
            const algos = await readAlgos(l, problemDir, `.${l}`);

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