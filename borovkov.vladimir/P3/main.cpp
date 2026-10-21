#include <iostream>
#include <string>
#include <fstream>

const int max_rows = 100;
const int max_cols = 100;
constexpr int invalid_terminal_elements = 1;
constexpr int invalid_elements_in_file = 2;

void delete_matrix(int** matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** create_matrix(int rows, int cols)
{
  int** matrix = new int* [rows]();
  try
  {
    for (int i = 0; i < rows; i++)
    {
      matrix[i] = new int[cols]();
    }
  }
  catch (...)
  {
    delete_matrix(matrix, rows, cols);
  }
  return matrix;
}


int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments";
    return invalid_terminal_elements;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments";
    return invalid_terminal_elements;
  }
  if (argc == 4)
  {
    int variant = 0;
    try
    {
      variant = std::stoi(argv[1]);
      if (variant != 1 && variant != 2)
      {
        throw std::out_of_range("First parametr is out of range");
      }
    }
    catch (const std::invalid_argument)
    {
      std::cerr << "First parameter is not a number";
      return invalid_terminal_elements;
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "First parametr is out of range";
      return invalid_terminal_elements;
    }
    if (variant == 1)
    {
      std::ifstream file_input(argv[2]);
      if (!file_input.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      if (file_input.peek() == std::ifstream::traits_type::eof())
      {
        std::cerr << "File is empty";
        return invalid_elements_in_file;
      }
      int matrix[max_rows][max_cols];
      int rows = 0;
      int cols = 0;
      if (!(file_input >> rows) || !(file_input >> cols))
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      if (rows < 0 || cols < 0)
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          int x = 0;
          if (!(file_input >> x))
          {
            std::cerr << "Incorrect element in file";
            return invalid_elements_in_file;
          }
          matrix[i][j] = x;
        }
      }
      file_input.close();
      if (rows == 0 || cols == 0)
      {
        std::ofstream file_output(argv[3]);
        if (!file_output.is_open())
        {
          std::cerr << "File can not open";
          return invalid_elements_in_file;
        }
        file_output << rows << " " << cols;
        file_output.close();
        return 0;
      }
      int rows_start = 0;
      int rows_end = rows - 1;
      int cols_start = 0;
      int cols_end = cols - 1;
      int increment = 1;
      while (rows_start <= rows_end && cols_start <= cols_end)
      {
        for (int i = cols_start; i <= cols_end; i++)
        {
          matrix[rows_end][i] += increment;
          increment++;
        }
        rows_end--;
        if (rows_start <= rows_end)
        {
          for (int i = rows_end; i >= rows_start; i--)
          {
            matrix[i][cols_end] += increment;
            increment++;
          }
          cols_end--;
        }
        if (cols_start <= cols_end)
        {
          for (int i = cols_end; i >= cols_start; i--)
          {
            matrix[rows_start][i] += increment;
            increment++;
          }
          rows_start++;
        }
        if (rows_start <= rows_end)
        {
          for (int i = rows_start; i <= rows_end; i++)
          {
            matrix[i][cols_start] += increment;
            increment++;
          }
          cols_start++;
        }
      }
      std::ofstream file_output(argv[3]);
      if (!file_output.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      file_output << rows << " " << cols;
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          file_output << " " << matrix[i][j];
        }
      }
      file_output.close();
    }
    if (variant == 2)
    {
      std::ifstream file_input(argv[2]);
      if (!file_input.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      if (file_input.peek() == std::ifstream::traits_type::eof())
      {
        std::cerr << "File is empty";
        return invalid_elements_in_file;
      }
      int rows = 0;
      int cols = 0;
      if (!(file_input >> rows) || !(file_input >> cols))
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      if (rows < 0 || cols < 0)
      {
        std::cerr << "Incorrect element in file";
        return invalid_elements_in_file;
      }
      int** matrix = create_matrix(rows, cols);
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          int x = 0;
          if (!(file_input >> x))
          {
            std::cerr << "Incorrect element in file";
            return invalid_elements_in_file;
          }
          matrix[i][j] = x;
        }
      }
      file_input.close();
      if (rows == 0 || cols == 0)
      {
        std::ofstream file_output(argv[3]);
        if (!file_output.is_open())
        {
          std::cerr << "File can not open";
          return invalid_elements_in_file;
        }
        file_output << rows << " " << cols;
        file_output.close();
        delete_matrix(matrix, rows, cols);
        return 0;
      }
      int rows_start = 0;
      int rows_end = rows - 1;
      int cols_start = 0;
      int cols_end = cols - 1;
      int increment = 1;
      while (rows_start <= rows_end && cols_start <= cols_end)
      {
        for (int i = cols_start; i <= cols_end; i++)
        {
          matrix[rows_end][i] += increment;
          increment++;
        }
        rows_end--;
        if (rows_start <= rows_end)
        {
          for (int i = rows_end; i >= rows_start; i--)
          {
            matrix[i][cols_end] += increment;
            increment++;
          }
          cols_end--;
        }
        if (cols_start <= cols_end)
        {
          for (int i = cols_end; i >= cols_start; i--)
          {
            matrix[rows_start][i] += increment;
            increment++;
          }
          rows_start++;
        }
        if (rows_start <= rows_end)
        {
          for (int i = rows_start; i <= rows_end; i++)
          {
            matrix[i][cols_start] += increment;
            increment++;
          }
          cols_start++;
        }
      }
      std::ofstream file_output(argv[3]);
      if (!file_output.is_open())
      {
        std::cerr << "File can not open";
        return invalid_elements_in_file;
      }
      file_output << rows << " " << cols;
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < cols; j++)
        {
          file_output << " " << matrix[i][j];
        }
      }
      delete_matrix(matrix, rows, cols);
      file_output.close();
    }
  }
  return 0;
}
