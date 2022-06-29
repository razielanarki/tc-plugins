#pragma once

#include <exception>
#include <concepts>

#include "utility.h" // is_any_same_v

namespace nonstd
{

inline namespace fundamentals_v3
{

// implementation details
namespace detail
{

// default scope exit policy
struct scope_exit_policy
{
    inline scope_exit_policy( bool execute_on_exit = true ) noexcept
        : execute_on_exit( execute_on_exit )
    {
    }

    inline scope_exit_policy( scope_exit_policy& rhs ) noexcept
        : execute_on_exit( rhs.execute_on_exit )
    {
    }

    inline bool engaged() const noexcept
    {
        return execute_on_exit;
    }

    inline void release() noexcept
    {
        execute_on_exit = false;
    }

protected:
    bool execute_on_exit;
};

// generic exception-based scope exit policy
struct scope_except_policy : scope_exit_policy
{
    inline scope_except_policy( bool execute_on_exit = true ) noexcept
        : scope_exit_policy( execute_on_exit )
        , uncaught_on_creation( std::uncaught_exceptions() )
    {
    }

    inline scope_except_policy( scope_except_policy&& rhs ) noexcept
        : scope_exit_policy( rhs )
        , uncaught_on_creation( rhs.uncaught_on_creation )
    {
    }

    inline bool engaged() const noexcept
        = delete;

protected:
    int uncaught_on_creation;
};

// scope fail exit policy
struct scope_fail_policy : scope_except_policy
{
    using scope_except_policy::scope_except_policy;

    inline bool engaged()
    {
        return ( scope_exit_policy::engaged() && std::uncaught_exceptions() > uncaught_on_creation );
    }
};

// scope success exit policy
struct scope_success_policy : scope_except_policy
{
    using scope_except_policy::scope_except_policy;

    inline bool engaged()
    {
        return ( scope_exit_policy::engaged() && std::uncaught_exceptions() <= uncaught_on_creation );
    }
};

// scope guard policy type constraint
template<class Policy>
concept scope_guard_policy = is_any_same_v<Policy, scope_exit_policy, scope_fail_policy, scope_success_policy>;

// generic scope-guard template
template<std::invocable ExitCallback, scope_guard_policy ExitPolicy>
class scope_guard
{
public:
    template<std::invocable Callback>
    inline scope_guard( Callback&& callback )
        noexcept( std::is_nothrow_constructible_v<ExitCallback, Callback> || std::is_nothrow_constructible_v<ExitCallback, Callback&> )
        requires( std::is_constructible_v<ExitCallback, Callback> )
        : exit_callback( std::forward<Callback>( callback ) )
        , exit_policy ()
    {
    }

    inline scope_guard( scope_guard&& rhs )
        noexcept( std::is_nothrow_move_constructible_v<ExitCallback> || std::is_nothrow_copy_constructible_v<ExitCallback> )
        requires( std::is_nothrow_move_constructible_v<ExitCallback> || std::is_copy_constructible_v<ExitCallback> )
        : exit_callback( std::move_if_noexcept( rhs.exit_callback ) )
        , exit_policy( rhs.exit_policy )
    {
        rhs.release();
    }

    inline scope_guard( const scope_guard& )
        = delete;

    inline scope_guard& operator=( const scope_guard& )
        = delete;

    inline scope_guard& operator=( scope_guard&& )
        = delete;

    inline ~scope_guard() noexcept
    {
        if( !exit_policy.engaged() )
            return;

        (void) exit_callback();
   }

    inline void release() noexcept
    {
        exit_policy.release();
    }

private:
    ExitCallback exit_callback;
    ExitPolicy exit_policy;
};

}

// scope_exit + deduction template
template<std::invocable ExitCallback> class scope_exit
    : public detail::scope_guard<ExitCallback, detail::scope_exit_policy>
{
};

template<std::invocable ExitCallback>
scope_exit( ExitCallback )->scope_exit<ExitCallback>;

// scope fail + deduction template
template<std::invocable ExitCallback> class scope_fail
    : public detail::scope_guard<ExitCallback, detail::scope_fail_policy>
{
};

template<std::invocable ExitCallback>
scope_fail( ExitCallback )->scope_fail<ExitCallback>;

// scope success + deduction template
template<std::invocable ExitCallback> class scope_success
    : public detail::scope_guard<ExitCallback, detail::scope_success_policy>
{
};

template<std::invocable ExitCallback>
scope_success( ExitCallback )->scope_success<ExitCallback>;

#if 0
inline namespace example
{

inline void constexpr_example()
{
    scope_exit( [] { return; } );

    // named storage
    scope_exit stored = scope_exit( [] { return; } );
    // cancelled
    stored.release();

    // list init
    scope_exit list_init { [] { return; } };
    // copy list init
    scope_exit copy_list_init = { [] { return; } };
    // copy_list_init = { [] { return; } }; // (reassign) ERROR: no operator matches ...
    // move
    scope_exit moved = std::move( stored );
    //scope_exit copied = stored; // (copy) ERROR: copy constructor deleted
}

inline void example()
{
    scope_exit( [] { return; } );

    // named storage
    scope_exit stored = scope_exit( [] { return; } );
    // cancelled
    stored.release();

    // list init
    scope_exit list_init { [] { return; } };
    // copy list init
    scope_exit copy_list_init = { [] { return; } };
    // copy_list_init = { [] { return; } }; // (reassign) ERROR: no operator matches ...
    // move
    scope_exit moved = std::move( stored );
    //scope_exit copied = stored; // (copy) ERROR: copy constructor deleted
}

}
#endif

//--------------------------------------------------------------------------

} // inline namesapce fundamentals_v3

} // namescpace nonstd

//==========================================================================
