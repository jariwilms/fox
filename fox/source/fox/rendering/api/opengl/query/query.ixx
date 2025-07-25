export module fox.rendering.api.opengl.query;

import std;

import fox.rendering.api.opengl;
import fox.rendering.base.query;

export namespace fox::gfx::api::gl
{
	class Query : public gl::Object
	{
	public:
		using Target = api::Query::Target;

		explicit Query(Target target)
			: gl::Object{ gl::create_query(gl::map_query_target(target)), [](auto* handle) { gl::delete_query(*handle); }}
			, target_{ target }
		{
			gl::todo();
		}

	private:
		Target target_;
	};
}
