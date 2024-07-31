# PODUM-ATPG
## _Path-Oriented Decision Making_

this is done for the completion of ECE 522 VLSI circuit testing

Build - make
Execution example - ./project c17.isc c17.pattern c17.res


The T-PODEM (Path-Oriented Decision Making) algorithm is a widely used method for Automatic Test Pattern Generation (ATPG) in VLSI circuits. It was developed to address the limitations of the D-Algorithm, particularly in generating test vectors for circuits with error correction and translation features.

Here’s a brief summary of the T-PODEM algorithm:

- Objective Definition: The algorithm starts by defining an objective, which could be fault activation, D-drive, or line justification.
- Backtracing: From the site of the objective, the algorithm backtraces to the primary inputs (PIs) to determine a value for a PI. This step uses testability measures for guidance.
- Simulation: The logic is simulated with the new PI value. If the objective is not accomplished but is still possible, the algorithm continues backtracing to another PI.
- Iteration: If the objective is accomplished but a test is not found, a new objective is defined, and the process repeats.
- X-PATH-CHECK: The algorithm uses the X-PATH-CHECK to ensure that a path of X’s from a D-frontier to a primary output (PO) exists. This step helps in verifying the propagation of the fault effect to the output.

The T-PODEM algorithm is efficient because it expands the binary decision tree only around primary inputs and uses backtracing to propagate values in forward directions, avoiding conflicts and unnecessary computations.
