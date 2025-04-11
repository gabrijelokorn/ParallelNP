#!/bin/bash
#SBATCH --job-name=ParallelNP
#SBATCH --output=out.log
#SBATCH --error=err.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=56
#SBATCH --time=01:00:00  # Max runtime (1 hour)
#SBATCH --partition=amd  # Use a valid CPU-only partition

make -s clean c check
