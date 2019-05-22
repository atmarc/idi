#version 330 core

out vec4 FragColor;

void main() {
    
    FragColor = vec4(1-(gl_FragCoord.x/708), gl_FragCoord.x/708, (gl_FragCoord.y/708), 1);
}

/*
EXERCICI 2:
    if (int(gl_FragCoord.y)%20 > 10) {
        if (gl_FragCoord.y < 354.) {
            if (gl_FragCoord.x < 354.) 
                FragColor = vec4(1, 1, 0, 1); //Groc
            else FragColor = vec4(0, 1, 0, 1); //Verd
        }
        else {
            if (gl_FragCoord.x < 354.) 
                FragColor = vec4(1, 0, 0, 1); // Vermell
            else FragColor = vec4(0, 0, 1, 1); //Blau
        }
    }
    else discard;
*/
