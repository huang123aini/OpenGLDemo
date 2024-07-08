#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient(环境光照)
    float ambientStrength = 0.1; //常量环境因子
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse(漫反射)
    /**
     *当计算光照时我们通常不关心一个向量的模长或它的位置，我们只关心它们的方向。所以，几乎所有的计算都使用单位向量完成
     */
    vec3 norm = normalize(Normal);

    //光的方向
    vec3 lightDir = normalize(lightPos - FragPos);
    
    /**
     * 对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫反射影响
     * 两个向量之间的角度越大，漫反射分量就会越小
     * 如果两个向量之间的角度大于90度，点乘的结果就会变成负数，这样会导致漫反射分量变为负数。
     * 为此，我们使用max函数返回两个参数之间较大的参数，从而保证漫反射分量不会变成负数
     */
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular(镜面反射)

    /**
     *观察向量是我们计算镜面光照时需要的一个额外变量，我们可以使用观察者的世界空间位置和片段的位置来计算它
     */
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);

    /**
     *需要注意的是我们对lightDir向量进行了取反。reflect函数要求第一个向量是从光源指向片段位置的向量
     */
    vec3 reflectDir = reflect(-lightDir, norm);  

    /**
     *这个32是高光的反光度(Shininess)。一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小
     */
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 