#ifndef COMPONENTSTORAGE_H
#define COMPONENTSTORAGE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "BaseComponentStorage.h"
#include "../World/IWorldInternal.h"

template <typename T>
class ComponentStorage final : public BaseComponentStorage {
    internal::IWorldInternal& _world;

    std::vector<T> _data;      // Для плотного хранения данных
    std::vector<int> _sparse;  // Для разреженного хранения индексов элементов (сущностей)
    std::vector<int> _dense;   // Для плотного хранения реально существующих элементов (сущностей, на которых есть компоненты)
    
    int _count = 0;            // Текущее число элементов

    int _id;

    void Resize(const int sparseSize, const int dataSize)
    {
        // ToDo: перевыделение памяти под вектора
        int oldSparseSize = _sparse.size();
        if (oldSparseSize < sparseSize)
        {
            _sparse.resize(sparseSize);
            std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize, -1);
        }
        int oldDataSize = _dense.size();
        if (oldDataSize < dataSize)
        {
            _dense.resize(dataSize);
            _data.resize(dataSize);
            std::fill_n(_dense.data() + oldDataSize, dataSize - oldDataSize, -1);
        }
    }

public:
    // ToDo:
    ComponentStorage(internal::IWorldInternal& w, const int id): _world(w), _id(id) {}

    bool Has(const int entityIid) const override
    {
        // ToDo: Проверка наличия компонента на сущности
        return entityIid >= 0 && entityIid < _sparse.size() && _sparse[entityIid] >= 0;
    }

    T& Get(const int entityIid)
    {
        // ToDo: Получение компонента с сущности
        return _data[_sparse[entityIid]];
    }

    T& Add(const int entityIid, const T& value)
    {
        // ToDo: Проверка необходимости ресайза
        Resize((entityIid / 64 + 1) * 64, _count >= _data.size() ? _data.size() + 64 : _data.size());
        // ToDo: Добавление компонента на сущность
        _data[_count] = value;
        _dense[_count] = entityIid;
        _sparse[entityIid] = _count;
        _count++;
        // ToDo: Уведомление мира об изменении набора компонентов на сущности
        _world.EntityComponentsChanged(entityIid, _id, true);
        return _data[_sparse[entityIid]];
    }

    void Remove(const int entityIid) override
    {
#if DEBUG
        if (!_world.IsEntityAlive(entityIid))
            throw std::runtime_error("Try to remove from dead entity!");
#endif
        // ToDo: FastRemove компонента с сущности
        int arrayIndex = _sparse[entityIid];
        int lastEntityIid = _dense[--_count];
        _data[arrayIndex] = _data[_count];
        _dense[arrayIndex] = lastEntityIid;
        _sparse[lastEntityIid] = arrayIndex;
        _sparse[entityIid] = -1;  
        // ToDo: Уведомление мира об изменении набора компонентов на сущности
        _world.EntityComponentsChanged(entityIid, _id, false);
    }

    // ToDo: возврат всех компонентов данного типа
    std::span<const T> All() const
    {
        return std::span(_data.begin(), _count);
    }
    // ToDo: возврат всех сущностей с компонентом данного типа
    std::span<const int> Entities() const override
    {
        return std::span(_dense.begin(), _count);
    }

    // ToDo:
    int Count() const override 
    { 
        return _count; 
    }

    int Id() const override 
    { 
       return _id; 
    }
};

#endif //COMPONENTSTORAGE_H

