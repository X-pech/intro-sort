# Сортировка

Я долго пытался выбрать какую сортировку реализовать и в итоге реализовал что-то вроде `std::sort` - комбинированную сортировку, которая:
* Быстра как `qsort`
* В случае для `qsort` не подходящем чтобы сохранить логарифмическую асимптотику использует кучу (воспользовался встроенными `std::make_heap`)
* В случае если элементов на подотрезке для сортировки мало, использует сортировку вставками (может быть *де-факто* быстрее для маленьких массивов из-за меньшей контстанты)