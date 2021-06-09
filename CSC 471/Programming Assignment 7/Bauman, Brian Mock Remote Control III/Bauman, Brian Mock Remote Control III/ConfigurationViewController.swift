//
//  ConfigurationViewController.swift
//  Bauman, Brian Mock Remote Control III
//
//  Created by Brian Bauman on 3/1/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ConfigurationViewController: UIViewController {

    @IBOutlet weak var channelLabel: UILabel!;
    @IBOutlet weak var labelTextField: UITextField!;
    @IBOutlet weak var buttonSegmentedControl: UISegmentedControl!;
    @IBOutlet weak var channelStepper: UIStepper!;
    
    var currentButton: Int = 0;
    var currentLabel: String = "";
    var currentChannel: String = "";
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        buttonSegmentedControl.selectedSegmentIndex = 0;
        currentLabel = config.labels[0];
        currentChannel = config.channels[0];
        
        labelTextField.text = currentLabel;
        channelLabel.text = currentChannel;
    }
    
    @IBAction func buttonWasChanged(_ sender: UISegmentedControl) {
        currentButton = sender.selectedSegmentIndex;
        currentLabel = config.labels[currentButton];
        currentChannel = config.channels[currentButton];
        
        labelTextField.text = currentLabel;
        channelLabel.text = currentChannel;
        if let channel = Double(currentChannel) {
            channelStepper.value = channel;
        }
    }
    
    @IBAction func editDidEnd(_ sender: UITextField) {
        sender.resignFirstResponder();
    }
    
    @IBAction func channelStepperWasPressed(_ sender: UIStepper) {
        currentChannel = String(format: "%02d", Int(sender.value));
        channelLabel.text = currentChannel;
    }
    
    @IBAction func saveButtonWasPressed() {
        if let text = labelTextField.text {
            if (text.count < 1 || text.count > 4) {
                let alertController = UIAlertController(title: "Invalid input", message: "Please enter a value containing 1-4 characters.", preferredStyle: .alert);
                let cancelAction = UIAlertAction(title: "OK", style: .cancel, handler: nil);
                alertController.addAction(cancelAction);
                present(alertController, animated: true, completion: nil);
            } else {
                currentLabel = text;
                config.labels[currentButton] = currentLabel;
                config.channels[currentButton] = currentChannel;
            }
        }
    }
    
    @IBAction func cancelButtonWasPressed() {
        currentLabel = config.labels[currentButton];
        currentChannel = config.channels[currentButton];
        
        labelTextField.text = currentLabel;
        channelLabel.text = currentChannel;
    }
}
