#ifndef _BI_CACHE_POOL_H__
#define _BI_CACHE_POOL_H__

//#include <mutex>
#include <atomic>

#include "buffer_item.h"

// BI_CACHE_POOL_SIZE should equal to 2^n <= 2 ^16
#define BI_CACHE_POOL_SIZE (1024 * 4)


class BICachePool {
public:
    BICachePool();

    BICachePool(const BICachePool &)=delete;
    BICachePool(const BICachePool &&)=delete;
    BICachePool &operator=(const BICachePool &)=delete;

public:
    BufferItem *get();
    void put(BufferItem *bi);

private:
  BufferItem **_cache;

  std::atomic_uint _w_r_index;

  //BufferItem *_head;
  //unsigned int _r_index;
  //std::mutex _mutex_r_index;

  //BufferItem *_tail;
  //unsigned int _w_index;
  //std::mutex _mutex_w_index;
};

extern BICachePool BI_CACHE_POOL;

#endif//_BI_CACHE_POOL_H__
