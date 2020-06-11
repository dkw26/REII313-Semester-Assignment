# REII 313 Semester Project

## Project members:

* Leonard Johannes Bronkhorst, 30051169, USERNAME: LehanBronkhorst
* Daniël Kloppers Wessels, 30316944, USERNAME: dkw26

## Compile Instructions

1. Open Qt
2. Click "open project" and browse to project location
3. Open [projectName].pro
4. Run the program
5. Click "Enter" or "Exit" button (Note Exit button will exit the application) 
6. Choose a Mixed-integer Linear Programming solver
7. If Simplex Method chosen:

* Enter the column size (tipically the amount of unknown variables)
* Enter the row size (typically the amount of equations)
* Enter the ammount of variables (usually the same as the column size)
* Enter the ammount of constraints (usually the same as row size)
* Click "Generate Matrix"
* Enter the objective fucntion coefficients in each cell corresponding to a variable number
* Enter capacity restraints that correspond to each equation
* Enter the matrix of coefficients in the equations that respond to each variable.
* Click Solve
* Click Done when finished and satisfied with answer.

8. If Branch-and-Bound Method chosen:

* Enter the number of items
* Click "Generate Matrix"
* Enter the values that correspond to each variable
* Enter the weights that correspond to each variable
* Enter the capacity of the problem
* Click Solve
* Click Done when finished and satisfied with answer.

## Test Cases
### 1. Simplex Method

Objective Function (Maximize): 2x + 5y + 4z

Subject to: 2x + y + z <= 180
            x + 3y + 2z <= 300
            2x + y + 2z <= 240

#### Thus:

Column size = 3
Row size = 3
Variable amount = 3
Constraints amount = 3

objective function: 

|    |1   |2   |3   |
|----|----|----|----|
|**1**   |6   |5   |4   |


capcity constraints: 
|    |1   |
|----|----|
|**1**   |180 |
|**2**   |300 |
|**3**   |240 |

matrix: 
|    |1   |2   |3   |
|----|----|----|----|
|**1**   |2 |1 |1 |
|**2**   |1 |3 |2 |
|**3**   |2 |1 |2 |

Maximum Value: 708

### 2. Branch-and-Bound Method

Value Function: 12x + 45y + 56z + 45w

Weights Function: 89x + 45y + 10z + 45w

Capacity: 16

#### Thus:

Number of items: 4

Values table:
|    |1   |2   |3   |4   |
|----|----|----|----|----|
|**1**   |12   |45   |56   |45   |

Weights table: 
|    |1   |2   |3   |4   |
|----|----|----|----|----|
|**1**   |89   |45   |10   |45   |

Optimal solution = 56
