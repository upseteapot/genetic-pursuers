#pragma once
#include <iostream>
#include <random>
#include <memory>


template <typename T>
class ProbArray
{
  public:
    ProbArray() = default;
    ~ProbArray();
    void create(std::size_t size);
    void push(const T &element, std::size_t frequency);
    const T& get_random();
  private:
    std::size_t m_index=0, m_size=0, m_total=0;
    std::size_t *m_frequencies;
    T *m_data;
};


#ifdef PROB_ARRAY_IMPLEMENTATION
#undef PROB_ARRAY_IMPLEMENTATION

template <typename T>
ProbArray<T>::~ProbArray()
{
  if (m_size > 0) {
    delete[] m_data;
    delete[] m_frequencies;
  }
}

template <typename T>
void ProbArray<T>::create(std::size_t size)
{
  m_size = size;
  m_data = new T[m_size];
  m_frequencies = new std::size_t[m_size];
}

template <typename T>
void ProbArray<T>::push(const T &element, std::size_t frequency)
{
  if (m_index < m_size) {
    m_total += frequency;
    m_data[m_index] = element;
    m_frequencies[m_index] = m_total;
    m_index++;
  } else {
    std::cout << "ERROR: Array has already reached its full capacity." << std::endl;
  }
}

template <typename T>
const T& ProbArray<T>::get_random()
{
  std::size_t random_index = std::round((float)m_total * ((float)rand() / (float)RAND_MAX));
  for (std::size_t i=0; i < m_size; i++) {
    if (random_index <= m_frequencies[i])
      return m_data[i];
  }
  std::cout << "ERROR: Random index could not be mached to any frequecy, returning the last element." << std::endl;
  return m_data[m_size - 1];
}

#endif

