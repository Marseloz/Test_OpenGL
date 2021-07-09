#version 400 core
in vec4 fColor;
in vec2 MausePos;
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main() {
    float lerpValue, max;
    float R = sqrt(pow((600-gl_FragCoord.y)-MausePos.y, 2)+pow(gl_FragCoord.x-MausePos.x, 2));
    max = 5+(ourColor.x+ourColor.y)*30;

    if(R <= max){

            lerpValue = 1;

    }
    else if(R <= max+1){
        lerpValue = (max+1)-R;
    }
    else {
        lerpValue = 0;
    }
    FragColor = mix(vec4(0.2f, 0.3f, 0.3f, 1.0f), ourColor, lerpValue);
}   
