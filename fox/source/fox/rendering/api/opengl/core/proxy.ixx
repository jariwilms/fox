export module fox.rendering.api.opengl.proxy;

import std;
import fox.rendering.api.opengl.concepts;

export namespace fox::gfx::api::gl
{
    template<typename... T> requires (gl::all_same_type<T...>)
    struct proxy_t
    {
        template<typename U> requires (std::is_convertible_v<U, T> && ...)
        constexpr proxy_t(const U&   element )
            : pack{ std::make_tuple(static_cast<T>(element)...) } {}
        constexpr proxy_t(      T... elements)
            : pack{ std::make_tuple(elements...) } {}

        template<typename Fn>
        void apply(Fn&& function)
        {
            std::apply([function](auto&&... element) { ((function(element)), ...); }, pack);
        }

        std::tuple<T...> pack;
    };
}
