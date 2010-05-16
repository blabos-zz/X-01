import br.edu.fei.cc4641.bolsa.*;

public class Market {
	public static void main(String[] args) {
		Book.init();
		
		@SuppressWarnings("unused")
		Server server = new Server(7070);
		
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		while(true) {
			try {
				Thread.sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}

}
