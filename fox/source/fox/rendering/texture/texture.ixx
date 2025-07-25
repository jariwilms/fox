export module fox.rendering.texture;

import std;
import fox.core.types;
import fox.core.meta;
import fox.rendering.api;
import fox.rendering.base.texture;

export namespace fox::gfx
{
    class Texture1D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        explicit Texture1D(std::shared_ptr<impl::Texture1D> _)
            : _{ _ } {}

        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions) -> std::shared_ptr<Texture1D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture1D>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture1D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture1D>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(Format format,                                   const fox::Vector1u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture1D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture1D>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::length_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::length_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s)
        {
            _->apply_wrapping({ s });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> Format
        {
            return _->format();
        }
        auto filter       () const -> Filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<Wrapping>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::Vector1u&
        {
            return _->dimensions();
        }
        auto mipmap_levels() const -> fox::uint32_t
        {
            return _->mipmap_levels();
        }
        auto handle       () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl         () const -> std::shared_ptr<impl::Texture1D>
        {
            return _;
        }

    protected:
        Texture1D(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions) } {}
        Texture1D(Format format, Filter filter, Wrapping wrapping, const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, filter, wrapping, dimensions, data) } {}
        Texture1D(Format format,                                   const fox::Vector1u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture1D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture1D> _;
    };
    class Texture2D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        explicit Texture2D(std::shared_ptr<impl::Texture2D> _)
            : _{ _ } {}

        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions) -> std::shared_ptr<Texture2D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture2D>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture2D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture2D>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture2D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture2D>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                     std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::area_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::area_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t)
        {
            _->apply_wrapping({ s, t });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> Format
        {
            return _->format();
        }
        auto filter       () const -> Filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<Wrapping, Wrapping>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::Vector2u&
        {
            return _->dimensions();
        }
        auto mipmap_levels() const -> fox::uint32_t
        {
            return _->mipmap_levels();
        }
        auto handle       () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl         () const -> std::shared_ptr<impl::Texture2D>
        {
            return _;
        }

    protected:
        Texture2D(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions) } {}
        Texture2D(Format format, Filter filter, Wrapping wrapping, const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, filter, wrapping, dimensions, data) } {}
        Texture2D(Format format,                                   const fox::Vector2u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture2D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture2D> _;
    };
    class Texture3D
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

        explicit Texture3D(std::shared_ptr<impl::Texture3D> _)
            : _{ _ } {}

        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions) -> std::shared_ptr<Texture3D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture3D>>(std::in_place_t{}, format, filter, wrapping, dimensions);
        }
        static auto create(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture3D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture3D>>(std::in_place_t{}, format, filter, wrapping, dimensions, data);
        }
        static auto create(Format format,                                   const fox::Vector3u& dimensions, std::span<const fox::byte_t> data) -> std::shared_ptr<Texture3D>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture3D>>(std::in_place_t{}, format, dimensions, data);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        void copy      (Format format,                       std::span<const fox::byte_t> data)
        {
            _->copy(format, data);
        }
        void copy_range(Format format, fox::volume_t region, std::span<const fox::byte_t> data)
        {
            _->copy_range(format, impl::volume_t{ region.extent, region.origin }, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t, Wrapping r)
        {
            _->apply_wrapping({ s, t, r });
        }
        void generate_mipmap()
        {
            _->generate_mipmap();
        }

        auto format       () const -> Format
        {
            return _->format();
        }
        auto filter       () const -> Filter
        {
            return _->filter();
        }
        auto wrapping     () const -> const std::tuple<Wrapping, Wrapping, Wrapping>&
        {
            return _->wrapping();
        }
        auto dimensions   () const -> const fox::Vector3u&
        {
            return _->dimensions();
        }
        auto mipmap_levels() const -> fox::uint32_t
        {
            return _->mipmap_levels();
        }
        auto handle       () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl         () const -> std::shared_ptr<impl::Texture3D>
        {
            return _;
        }

    protected:
        Texture3D(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions) } {}
        Texture3D(Format format, Filter filter, Wrapping wrapping, const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, filter, wrapping, dimensions, data) } {}
        Texture3D(Format format,                                   const fox::Vector3u& dimensions, std::span<const fox::byte_t> data)
            : _{ std::make_shared<impl::Texture3D>(format, dimensions, data) } {}

    private:
        std::shared_ptr<impl::Texture3D> _;
    };

    class Texture2DMultisample
    {
    public:
        using Format = api::Texture::Format;

        explicit Texture2DMultisample(std::shared_ptr<impl::Texture2DMultisample> _)
            : _{ _ } {}

        static auto create(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples) -> std::shared_ptr<Texture2DMultisample>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture2DMultisample>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        auto format    () const -> Format
        {
            return _->format();
        }
        auto samples   () const -> fox::uint32_t
        {
            return _->samples();
        }
        auto dimensions() const -> const fox::Vector2u&
        {
            return _->dimensions();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::Texture2DMultisample>
        {
            return _;
        }

    protected:
        Texture2DMultisample(Format format, const fox::Vector2u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture2DMultisample>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::Texture2DMultisample> _;
    };
    class Texture3DMultisample
    {
    public:
        using Format = api::Texture::Format;

        explicit Texture3DMultisample(std::shared_ptr<impl::Texture3DMultisample> _)
            : _{ _ } {}

        static auto create(Format format, const fox::Vector3u& dimensions, fox::uint32_t samples) -> std::shared_ptr<Texture3DMultisample>
        {
            return std::make_shared<meta::from_inaccessible_ctor<Texture3DMultisample>>(std::in_place_t{}, format, dimensions, samples);
        }

        void bind(gfx::binding_t binding) const
        {
            _->bind(static_cast<impl::binding_t>(binding));
        }

        auto format    () const -> Format
        {
            return _->format();
        }
        auto dimensions() const -> const fox::Vector3u&
        {
            return _->dimensions();
        }
        auto samples   () const -> fox::uint32_t
        {
            return _->samples();
        }
        auto handle    () const -> gfx::handle_t
        {
            return _->handle();
        }
        auto impl      () const -> std::shared_ptr<impl::Texture3DMultisample>
        {
            return _;
        }

    protected:
        Texture3DMultisample(Format format, const fox::Vector3u& dimensions, fox::uint32_t samples)
            : _{ std::make_shared<impl::Texture3DMultisample>(format, dimensions, samples) } {}

    private:
        std::shared_ptr<impl::Texture3DMultisample> _;
    };
}
