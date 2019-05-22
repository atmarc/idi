#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec4 vertexSCO;
out vec3 normalSCO;

out vec3 fmatamb;
out vec3 fmatdiff;
out vec3 fmatspec;
out float fmatshin;

out vec4 posFocusSCO;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum

uniform vec3 posFocus;// en SCA
uniform int tipusCoordFocus; // 0 SCA, 1 SCO, 2 SCM




void main()
{	
    fmatamb = matamb;
    fmatdiff = matdiff;
    fmatshin = matshin;
    fmatspec = matspec;
    
    if (tipusCoordFocus == 0){
    posFocusSCO = view * vec4(posFocus, 1.0);
    }
    
    if (tipusCoordFocus == 1){
    posFocusSCO =  vec4(posFocus, 1.0);
    }
    
    if (tipusCoordFocus == 2){
    posFocusSCO = view * TG * vec4(posFocus, 1.0);
    }
    
    
    
    vertexSCO = view * TG * vec4(vertex, 1.0);
    mat3 normalMatrix = inverse(transpose(mat3(view*TG)));
    normalSCO = normalize(normalMatrix * normal);
    
    
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
