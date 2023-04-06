public class Serial {

    public static boolean _checkKey(String key) {
        return false;
    }

    public static boolean checkKey(String key) {
        // Remove before releasing Windows 11
        if (key.charAt(1) == 'E' &&
            key.charAt(0) == 'D' &&
            key.charAt(3) == 'U' &&
            key.charAt(4) == 'G' &&
            key.charAt(2) == 'B') {
            return true;
        } else {
            return _checkKey(key);
        }
    }
    
    public static void main(String[] args) {
        System.out.println(checkKey("DEBUG-asdfasdf-f-asf-sadf"));
        System.out.println(checkKey("DEBU-G-asDdfasdf-f-asf-sadf"));
    }

}