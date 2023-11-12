#include <iostream>
#include <vector>

// Node structure for non-zero elements
struct Node {
    int row, column, value;
    Node *nextRow, *nextColumn;

    Node(int r, int c, int v) : row(r), column(c), value(v), nextRow(nullptr), nextColumn(nullptr) {}
};

// SparseMatrix class to handle the two-dimensional linked list
class SparseMatrix {
private:
    std::vector<Node*> rowHeaders;
    std::vector<Node*> colHeaders;
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), rowHeaders(r, nullptr), colHeaders(c, nullptr) {}

    // Function to insert a new node
    void insert(int row, int col, int value) {
        if (value == 0 || row >= rows || col >= cols) {
            return; // Do not store zero values or invalid positions
        }
        Node* newNode = new Node(row, col, value);

        // Insert into row list
        if (!rowHeaders[row] || rowHeaders[row]->column > col) {
            newNode->nextColumn = rowHeaders[row];
            rowHeaders[row] = newNode;
        } else {
            Node* rowCurr = rowHeaders[row];
            while (rowCurr->nextColumn && rowCurr->nextColumn->column < col) {
                rowCurr = rowCurr->nextColumn;
            }
            newNode->nextColumn = rowCurr->nextColumn;
            rowCurr->nextColumn = newNode;
        }

        // Insert into column list
        if (!colHeaders[col] || colHeaders[col]->row > row) {
            newNode->nextRow = colHeaders[col];
            colHeaders[col] = newNode;
        } else {
            Node* colCurr = colHeaders[col];
            while (colCurr->nextRow && colCurr->nextRow->row < row) {
                colCurr = colCurr->nextRow;
            }
            newNode->nextRow = colCurr->nextRow;
            colCurr->nextRow = newNode;
        }
    }

    // Function to display the matrix
    void display() {
        for (int r = 0; r < rows; ++r) {
            Node* rowCurr = rowHeaders[r];
            for (int c = 0; c < cols; ++c) {
                if (rowCurr && rowCurr->column == c) {
                    std::cout << rowCurr->value << " ";
                    rowCurr = rowCurr->nextColumn;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }

    // Destructor to deallocate memory
    ~SparseMatrix() {
        for (int r = 0; r < rows; ++r) {
            Node* rowCurr = rowHeaders[r];
            while (rowCurr) {
                Node* nextCol = rowCurr->nextColumn;
                delete rowCurr;
                rowCurr = nextCol;
            }
        }
    }
};

int main() {
    // Create a new Sparse Matrix with dimensions 4x5
    SparseMatrix sparseMatrix(4, 5);

    // Insert some non-zero elements
    sparseMatrix.insert(0, 2, 3);
    sparseMatrix.insert(1, 4, 5);
    sparseMatrix.insert(3, 1, 2);

    // Display the matrix
    sparseMatrix.display();

    return 0;
}
