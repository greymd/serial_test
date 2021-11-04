use std::time::Duration;
use serialport;
use chrono;
fn main() {
    let mut port = serialport::new("/dev/ttyS0", 115_200)
        .timeout(Duration::from_millis(10))
        .open().expect("Failed to open port");
    loop {
        let msg = format!("[{}] test test test test test test", chrono::offset::Local::now());
        let output = msg.as_bytes();
        eprintln!("{}", msg);
        port.write(output).expect("Write failed!");
    }
}
