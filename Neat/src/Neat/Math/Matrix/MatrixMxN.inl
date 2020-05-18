#include <iomanip>


namespace Neat
{
   template <UInt M, UInt N, typename T>
   std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& m)
   {
      os << "Matrix<" << N << ", " << M << ", " << typeid(T).name() << "> [";
      for (std::size_t i = 0; i < M; ++i)
      {
         os << "\n[";
         for (std::size_t j = 0; j < N; ++j)
         {
            if (j < N - 1)
               os << std::setw(10) << std::setprecision(6)
                  << m(i * N + j) << ", ";
            else
               os << std::setw(10) << std::setprecision(6)
                  << m(i * N + j);
         }
         os << "]";
      }
      os << "]\n";

      return os;
   }
}