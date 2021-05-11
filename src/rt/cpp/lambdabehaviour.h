// Copyright Microsoft and Project Verona Contributors.
// SPDX-License-Identifier: MIT
#pragma once

#include "../sched/cown.h"

namespace verona::rt
{
  using namespace snmalloc;

  template<class T>
  class LambdaBehaviour : public Behaviour
  {
    friend class Cown;

  private:
    T fn;

    static void f(Behaviour* msg)
    {
      auto t = static_cast<LambdaBehaviour<T>*>(msg);
      t->fn();

      if constexpr (!std::is_trivially_destructible_v<T>)
      {
        t->~T();
      }
    }

    static const Behaviour::Descriptor* desc()
    {
      static constexpr Behaviour::Descriptor desc = {sizeof(T), f, NULL};

      return &desc;
    }

  public:
    LambdaBehaviour(T fn_) : Behaviour(desc()), fn(fn_) {}
  };

  template<typename T>
  static void scheduleLambda(Cown* c, T f)
  {
    Cown::schedule<LambdaBehaviour<T>>(c, f);
  }
} // namespace verona::rt
