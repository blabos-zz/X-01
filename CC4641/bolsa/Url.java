

class Url {

    public static void main(String args[]) {
        String url = "chave1=valor1&chave2=valor2&chave3=valor3";
        
        String pairs[] = url.split("&");
        
        for (int i = 0; i < pairs.length; i++) {
            String tmp[] = pairs[i].split("=");
            System.out.println(tmp[0] + ": " + tmp[1]);
        }
        
    }
};
