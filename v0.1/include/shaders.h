const struct Textured {
	const char *vert =
		"#version 460\
		layout (location = 0) in vec3 a_position;\
		layout (location = 1) in vec2 a_tex_coord;\
		out vec2 v_tex_coord;\
		void main() {\
			v_tex_coord = a_tex_coord;\
			gl_Position = vec4(a_position, 1.0f);\
		};";
	const char * frag =
		"#version 460\
		in vec2 v_tex_coord;\
		uniform sampler2D u_texture;\
		out vec4 FragColor;\
		void main() {\
			FragColor = vec4(texture(u_texture, v_tex_coord).rrr, 1.0f);\
		};";	
} Textured;

const struct RectangleTextured {
	const char *vert =
		"#version 460\
		layout (location=0) in vec3 a_position;\
		layout (location=1) in vec2 a_dimensions;\
		layout (location=2) in vec2 a_texPosition;\
		layout (location=3) in vec2 a_texDimensions;\
		out vec2 v_dimensions;\
		out vec3 v_color;\
		out vec4 v_packedTex;\
		void main() {\
			v_dimensions = a_dimensions;\
			v_packedTex = vec4(a_texPosition.xy, a_texDimensions.xy);\
			gl_Position = vec4(a_position, 1.0f);\
		};";
	const char *geo=
		"#version 460\
		layout (points) in;\
		layout (triangle_strip, max_vertices = 4) out;\
		in vec2 v_dimensions[];\
		in vec3 v_color[];\
		in vec4 v_packedTex[];\
		out vec2 g_texCoord;\
		void main() {\
			vec4 p2 = gl_in[0].gl_Position + vec4(v_dimensions[0].xy, 0.0f, 0.0f);\
			vec2 t2 = v_packedTex[0].xy + v_packedTex[0].zw;\
			gl_Position = gl_in[0].gl_Position.xyzw;\
			g_texCoord = vec2(v_packedTex[0].xy);\
			EmitVertex();\
			gl_Position = vec4(gl_in[0].gl_Position.x, p2.yzw);\
			g_texCoord = vec2(v_packedTex[0].x, t2.y);\
			EmitVertex();\
			gl_Position = vec4(p2.x, gl_in[0].gl_Position.yzw);\
			g_texCoord = vec2(t2.x, v_packedTex[0].y);\
			EmitVertex();\
			gl_Position = p2.xyzw;\
			g_texCoord = t2;\
			EmitVertex();\
			EndPrimitive();\
		};";
	const char *frag=
	"#version 460\
	uniform sampler2D u_texture;\
	in vec2 g_texCoord;\
	out vec4 FragColor;\
	void main() {\
		FragColor = texture(u_texture, g_texCoord);\
	};";
} RectangleTextured;

const struct Rectangle {
	const char *vert=
		"#version 460\
		layout (location=0) in vec3 a_position;\
		layout (location=1) in vec2 a_dimensions;\
		layout (location=2) in vec3 a_color;\
		out vec2 v_dimensions;\
		out vec3 v_color;\
		void main() {\
			v_color = a_color;\
			v_dimensions = a_dimensions;\
			gl_Position = vec4(a_position, 1.0f);\
		};";
	
	const char *geo=
		"#version 460\
		layout (points) in;\
		layout (triangle_strip, max_vertices = 4) out;\
		in vec2 v_dimensions[];\
		in vec3 v_color[];\
		out vec3 g_color;\
		void main() {\
			g_color = v_color[0];\
			vec4 p2 = gl_in[0].gl_Position + vec4(v_dimensions[0].xy, 0.0f, 0.0f);\
			gl_Position = gl_in[0].gl_Position.xyzw;\
			EmitVertex();\
			gl_Position = vec4(gl_in[0].gl_Position.x, p2.yzw);\
			EmitVertex();\
			gl_Position = vec4(p2.x, gl_in[0].gl_Position.yzw);\
			EmitVertex();\
			gl_Position = p2.xyzw;\
			EmitVertex();\
			EndPrimitive();\
		};";
	
	const char *frag=
		"#version 460\
		in vec3 g_color;\
		out vec4 FragColor;\
		void main() {\
			FragColor = vec4(g_color, 1.0f);\
		};";

} Rectangle;

const struct StringRectangle {
	const char *vert=
		"#version 460\
		layout (location=0) in vec3 a_position;\
		layout (location=1) in vec2 a_dimensions;\
		layout (location=2) in vec3 a_color;\
		out vec2 v_dimensions;\
		out vec3 v_color;\
		void main() {\
			v_dimensions = a_dimensions;\
			v_color = a_color;\
			gl_Position = vec4(a_position, 1.0f);\
		};";
	
	const char *geo=
		"#version 460\
		layout (points) in;\
		layout (triangle_strip, max_vertices = 4) out;\
		in vec2 v_dimensions[];\
		in vec3 v_color[];\
		out vec2 g_texCoord;\
		out vec3 g_color;\
		void main() {\
			g_color = v_color[0];\
			vec4 p2 = gl_in[0].gl_Position + vec4(v_dimensions[0].xy, 0.0f, 0.0f);\
			gl_Position = gl_in[0].gl_Position.xyzw;\
			g_texCoord = vec2(0.0f,1.0f);\
			EmitVertex();\
			gl_Position = vec4(gl_in[0].gl_Position.x, p2.yzw);\
			g_texCoord = vec2(0.0f, 0.0f);\
			EmitVertex();\
			gl_Position = vec4(p2.x, gl_in[0].gl_Position.yzw);\
			g_texCoord = vec2(1.0f, 1.0f);\
			EmitVertex();\
			gl_Position = p2.xyzw;\
			g_texCoord = vec2(1.0f,0.0f);\
			EmitVertex();\
			EndPrimitive();\
		};";

	const char *frag=
		"#version 460\
		uniform sampler2D u_texture;\
		in vec2 g_texCoord;\
		in vec3 g_color;\
		out vec4 FragColor;\
		void main() {\
			FragColor = texture(u_texture, g_texCoord) * vec4(g_color.xyz, 1.0f);\
			if (FragColor.w < 0.5f) {\
				discard;\
			};\
		};";
} StringRectangle;