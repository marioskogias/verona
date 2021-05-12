// Copyright Microsoft and Project Verona Contributors.
// SPDX-License-Identifier: MIT
#pragma once

namespace verona::rt
{
  template<typename T>
  class Promise : public VCown<Promise<T>>
  {
  private:
    T val;

  public:
    Promise()
    {
      VCown<Promise<T>>::wake();
    }

    void fulfil(T v)
    {
      val = v;
      VCown<Promise<T>>::schedule();
    }

    template<typename F>
    void then(F fn)
    {
      scheduleLambda(this, fn);
    }

    T get()
    {
      return val;
    }
  };
}
