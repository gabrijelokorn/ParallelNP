const fs = require('fs').promises;
const { constants } = require('fs');

const languages = ["c", "julia", "golang"];
const programType = ["sequential", "parallel"];
// const programType = ["sequential"];
const algorithms = ["big_partition", "small_partitions", "Kamada-Kawai"];

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
            return csvParse(data, { columns: true, skip_empty_lines: true });
        })
        .catch(err => {
            return false;
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
        console.log("Error reading files: ", err);
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


async function test() {
    const big_partitionTests = await readTests("big_partition");
    const small_partitionsTests = await readTests("small_partitions");
    const Kamada_KawaiTests = await readTests("Kamada-Kawai");

    for (let a of algorithms) {
        for (let p of programType) {
            if (a === "big_partition") {
                for (let test of big_partitionTests) {
                    const array = [];
                    for (let l of languages) {
                        array.push(`${l}/${p}/${a}/output${test}.json`);
                    }
                    console.log(array);
                    const file1 = await fileExists(array[0]);
                    const file2 = await fileExists(array[1]);
                    const file3 = await fileExists(array[2]);

                    if (file1 && file2) {
                        const result1 = await compareFiles(array[0], array[1]);
                        console.log("Result1: ", result1);
                    }
                    if (file1 && file3) {
                        const result2 = await compareFiles(array[0], array[2]);
                        console.log("Result2: ", result2);
                    }
                    if (file2 && file3) {
                        const result3 = await compareFiles(array[1], array[2]);
                        console.log("Result3: ", result3);
                    }
                }
            }
            if (a === "small_partitions") {
                for (let test of small_partitionsTests) {
                    const array = [];
                    for (let l of languages) {
                        array.push(`${l}/${p}/${a}/output${test}.json`);
                    }
                }
            }
            if (a === "Kamada-Kawai") {
                for (let test of Kamada_KawaiTests) {
                    const arrayP = [];
                    const arrayC = [];
                    const arrayE = [];
                    for (let l of languages) {
                        arrayP.push(`${l}/${p}/${a}/points${test}.csv`);
                        arrayC.push(`${l}/${p}/${a}/coords${test}.csv`);
                        arrayE.push(`${l}/${p}/${a}/edges${test}.csv`);
                    }
                }
            }
        }
    }
}

test();