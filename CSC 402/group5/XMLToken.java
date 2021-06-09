package group5;
//Author: Brian Bauman

public class XMLToken {

	private String token;
	
	XMLToken(String token) {
		this.token = token.trim();
	}
	
	public boolean isTag() {
		if (token.length() <= 2) return false;
		
		char[] characters = token.toCharArray();
		
		//Check for opening and closing angle brackets
		if (characters[0] != '<' ||
			characters[characters.length - 1] != '>') return false;
		
		//Check for valid tag name characters
		for (int i = 1; i < characters.length - 1; i++) {		
			if (characters[i] == '/' && 
				i > 1 &&
				i < characters.length - 2) return false;
			
			if (!(characters[i] >= 47 && characters[i] < 58) &&
				!(characters[i] >= 65 && characters[i] < 91) &&
				!(characters[i] >= 97 && characters[i] < 123) &&
				!(characters[i] == 45)) return false;			
		}
		
		//Check proper placement of '/' character
		if (characters[1] == '/' &&
			characters[characters.length - 2] == '/') return false;
		
		return true;
	}
	
	public boolean isData() {
		if (this.isTag()) return false;
		
		for (char character : token.toCharArray()) {
			if (!(character >= 33 && character < 127) ||
				character == 60 ||
				character == 62) return false;
		}
		
		return true;
	}
	
	public boolean isClosingTag() {
		if (!this.isTag()) return false;
		if (token.toCharArray()[1] != '/') return false;
		
		return true;
	}
	
	public boolean isOpeningTag() {
		if (!this.isTag()) return false;
		
		char[] characters = token.toCharArray();
		if (characters[1] == '/' ||
			characters[characters.length - 2] == '/') return false;
		
		return true;
	}
	
	public boolean isSelfClosingTag() {
		if (!this.isTag()) return false;
		if (token.toCharArray()[token.length() - 2] != '/') return false;
		
		return true;
	}
	
	public String tagName() {
		if (this.isClosingTag()) return token.substring(2, token.length() - 1);
		if (this.isOpeningTag()) return token.substring(1, token.length() - 1);
		if (this.isSelfClosingTag()) return token.substring(1, token.length() - 3);
		return null;
	}
	
	public String toString() {
		return token;
	}
}
