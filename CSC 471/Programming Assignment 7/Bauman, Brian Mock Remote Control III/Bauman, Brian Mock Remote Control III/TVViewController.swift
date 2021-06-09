//
//  FirstViewController.swift
//  Bauman, Brian Mock Remote Control III
//
//  Created by Brian Bauman on 3/1/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

let config = Configuration();

class TVViewController: UIViewController {
    
    @IBOutlet weak var tvPowerLabel: UILabel!;
    @IBOutlet weak var speakerVolumeLabel: UILabel!;
    @IBOutlet weak var currentChannelLabel: UILabel!;
    
    @IBOutlet weak var tvPowerSwitch: UISwitch!;
    @IBOutlet weak var volumeSlider: UISlider!;
    @IBOutlet weak var zeroButton: UIButton!;
    @IBOutlet weak var oneButton: UIButton!;
    @IBOutlet weak var twoButton: UIButton!;
    @IBOutlet weak var threeButton: UIButton!;
    @IBOutlet weak var fourButton: UIButton!;
    @IBOutlet weak var fiveButton: UIButton!;
    @IBOutlet weak var sixButton: UIButton!;
    @IBOutlet weak var sevenButton: UIButton!;
    @IBOutlet weak var eightButton: UIButton!;
    @IBOutlet weak var nineButton: UIButton!;
    @IBOutlet weak var channelUpButton: UIButton!;
    @IBOutlet weak var channelDownButton: UIButton!;
    @IBOutlet weak var favoriteChannelControl: UISegmentedControl!;
    
    var firstDigitPressed: Bool = false;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //reset settings
        tvPowerLabel.text = "Off";
        speakerVolumeLabel.text = "00";
        currentChannelLabel.text = "01"
        tvPowerSwitch.isOn = false;
        volumeSlider.value = 0;
        volumeSlider.isEnabled = false;
        zeroButton.isEnabled = false;
        oneButton.isEnabled = false;
        twoButton.isEnabled = false;
        threeButton.isEnabled = false;
        fourButton.isEnabled = false;
        fiveButton.isEnabled = false;
        sixButton.isEnabled = false;
        sevenButton.isEnabled = false;
        eightButton.isEnabled = false;
        nineButton.isEnabled = false;
        channelUpButton.isEnabled = false;
        channelDownButton.isEnabled = false;
        favoriteChannelControl.isEnabled = false;
        favoriteChannelControl.selectedSegmentIndex = 0;
    }
    
    override func viewWillAppear(_ animated: Bool) {
        favoriteChannelControl.setTitle(config.labels[0], forSegmentAt: 0);
        favoriteChannelControl.setTitle(config.labels[1], forSegmentAt: 1);
        favoriteChannelControl.setTitle(config.labels[2], forSegmentAt: 2);
        favoriteChannelControl.setTitle(config.labels[3], forSegmentAt: 3);
    }
    
    @IBAction func powerToggleDidChange(sender: UISwitch) {
        if sender.isOn {
            tvPowerLabel.text = "On";
            volumeSlider.isEnabled = true;
            zeroButton.isEnabled = true;
            oneButton.isEnabled = true;
            twoButton.isEnabled = true;
            threeButton.isEnabled = true;
            fourButton.isEnabled = true;
            fiveButton.isEnabled = true;
            sixButton.isEnabled = true;
            sevenButton.isEnabled = true;
            eightButton.isEnabled = true;
            nineButton.isEnabled = true;
            channelUpButton.isEnabled = true;
            channelDownButton.isEnabled = true;
            favoriteChannelControl.isEnabled = true;
        } else {
            tvPowerLabel.text = "Off";
            volumeSlider.isEnabled = false;
            zeroButton.isEnabled = false;
            oneButton.isEnabled = false;
            twoButton.isEnabled = false;
            threeButton.isEnabled = false;
            fourButton.isEnabled = false;
            fiveButton.isEnabled = false;
            sixButton.isEnabled = false;
            sevenButton.isEnabled = false;
            eightButton.isEnabled = false;
            nineButton.isEnabled = false;
            channelUpButton.isEnabled = false;
            channelDownButton.isEnabled = false;
            favoriteChannelControl.isEnabled = false;
        }
    }
    
    @IBAction func volumeSliderDidChange(sender: UISlider) {
        speakerVolumeLabel.text = String(Int(sender.value * 100));
    }
    
    @IBAction func channelNumberWasPressed(sender: UIButton) {
        if let number = sender.currentTitle,
            let currentChannelText = currentChannelLabel.text {
            if firstDigitPressed {
                currentChannelLabel.text = currentChannelText + number;
                if (currentChannelLabel.text == "00") {
                    currentChannelLabel.text = "01";
                }
                firstDigitPressed = false;
            } else {
                currentChannelLabel.text = number;
                firstDigitPressed = true;
            }
        }
    }
    
    @IBAction func channelUpWasPressed(sender: UIButton) {
        if let text = currentChannelLabel.text,
            let number = Int(text) {
            if number < 99 {
                currentChannelLabel.text = String(format: "%02d", number + 1);
            } else if number == 99 {
                currentChannelLabel.text = "01";
            }
        }
    }
    
    @IBAction func channelDownWasPressed(sender: UIButton) {
        if let text = currentChannelLabel.text,
            let number = Int(text) {
            if number > 1 {
                currentChannelLabel.text = String(format: "%02d", number - 1);
            } else if number == 1 {
                currentChannelLabel.text = "99";
            }
        }
    }
    
    @IBAction func favoriteChannelWasChanged(sender: UISegmentedControl) {
        var channel = "";
        switch sender.selectedSegmentIndex {
        case 0:
            channel = config.channels[0];
            break;
        case 1:
            channel = config.channels[1];
            break;
        case 2:
            channel = config.channels[2];
            break;
        case 3:
            channel = config.channels[3];
            break;
        default:
            //do nothing
            channel = "01";
            break;
        }
        
        currentChannelLabel.text = channel;
    }
}

