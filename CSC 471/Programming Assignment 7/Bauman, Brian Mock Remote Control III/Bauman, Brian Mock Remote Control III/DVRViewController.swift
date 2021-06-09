//
//  SecondViewController.swift
//  Bauman, Brian Mock Remote Control III
//
//  Created by Brian Bauman on 3/1/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class DVRViewController: UIViewController {
    
    @IBOutlet weak var powerLabel: UILabel!;
    @IBOutlet weak var stateLabel: UILabel!;
    
    @IBOutlet weak var powerSwitch: UISwitch!;
    @IBOutlet weak var playButton: UIButton!;
    @IBOutlet weak var stopButton: UIButton!;
    @IBOutlet weak var pauseButton: UIButton!;
    @IBOutlet weak var fastForwardButton: UIButton!;
    @IBOutlet weak var fastRewindButton: UIButton!;
    @IBOutlet weak var recordButton: UIButton!;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        powerSwitch.isOn = false;
        stateLabel.text = "Off";
        
        playButton.isEnabled = false;
        stopButton.isEnabled = false;
        pauseButton.isEnabled = false;
        fastForwardButton.isEnabled = false;
        fastRewindButton.isEnabled = false;
        recordButton.isEnabled = false;
    }
    
    @IBAction func powerSwitchWasToggled(_ sender: UISwitch) {
        if sender.isOn {
            powerLabel.text = "On";
            stateLabel.text  = "Stopped";
            
            playButton.isEnabled = true;
            stopButton.isEnabled = true;
            pauseButton.isEnabled = true;
            fastForwardButton.isEnabled = true;
            fastRewindButton.isEnabled = true;
            recordButton.isEnabled = true;
        } else {
            powerLabel.text = "Off";
            stateLabel.text = "Off";
            
            playButton.isEnabled = false;
            stopButton.isEnabled = false;
            pauseButton.isEnabled = false;
            fastForwardButton.isEnabled = false;
            fastRewindButton.isEnabled = false;
            recordButton.isEnabled = false;
        }
    }
    
    @IBAction func buttonWasPressed(_ sender: UIButton) {
        if let label = sender.currentTitle {
            switch (label) {
            case "Play":
                if stateLabel.text != "Recording" {
                    stateLabel.text = "Playing";
                } else { handleIllegalAction(triedTo: "Play", while: stateLabel.text!); }
                break;
            case "Stop":
                stateLabel.text = "Stopped";
                break;
            case "Pause":
                if stateLabel.text == "Playing" {
                    stateLabel.text = "Paused";
                } else { handleIllegalAction(triedTo: "Pause", while: stateLabel.text!); }
                break;
            case "Fast Forward":
                if stateLabel.text == "Playing" {
                    stateLabel.text = "Fast forwarding";
                } else { handleIllegalAction(triedTo: "Fast Forward", while: stateLabel.text!); }
                break;
            case "Fast Rewind":
                if stateLabel.text == "Playing" {
                    stateLabel.text = "Fast rewinding";
                } else { handleIllegalAction(triedTo: "Fast Rewind", while: stateLabel.text!); }
                break;
            case "Record":
                if stateLabel.text == "Stopped" {
                    stateLabel.text = "Recording";
                } else { handleIllegalAction(triedTo: "Record",  while: stateLabel.text!); }
                break;
            default:
                break;
            }
        }
    }
    
    func handleIllegalAction(triedTo requestedAction: String, while currentState: String) {
        let alertController = UIAlertController(title: "Invalid selection", message: "Warning, cannot \(requestedAction.lowercased()) while \(currentState.lowercased()).", preferredStyle: .actionSheet);
        let cancelAction = UIAlertAction(title: "OK", style: .cancel, handler: nil);
        let forceAction = UIAlertAction(title: "Force action", style: .destructive) { _ in switch(requestedAction) {
            case "Play":
                self.stateLabel.text = "Playing";
                break;
            case "Stop":
                self.stateLabel.text = "Stopped";
                break;
            case "Pause":
                self.stateLabel.text = "Paused";
                break;
            case "Fast Forward":
                self.stateLabel.text = "Fast forwarding";
                break;
            case "Fast Rewind":
                self.stateLabel.text = "Fast rewinding";
                break;
            case "Record":
                self.stateLabel.text = "Recording";
                break;
            default:
                break;
            
            }
            
            self.alertOnForcedActionChange(from: currentState, to: requestedAction);
        };
        alertController.addAction(cancelAction);
        alertController.addAction(forceAction);
        present(alertController, animated: true, completion: nil);
    }
    
    func alertOnForcedActionChange(from currentAction: String, to requestedAction: String) {
        let alertController = UIAlertController(title: "Action forced", message: "State forced from \(currentAction.lowercased()) to \(requestedAction.lowercased()).", preferredStyle: .alert);
        let cancelAction = UIAlertAction(title: "OK", style: .cancel, handler: nil);
        alertController.addAction(cancelAction);
        present(alertController, animated: true, completion: nil);
    }
}


