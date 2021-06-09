//
//  ViewController.swift
//  Bauman, Brian Know Your Apostles
//
//  Created by Brian Bauman on 3/11/19.
//  Copyright © 2019 Brian Bauman. All rights reserved.
//

import UIKit

class ApostleListViewController: UITableViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Potentially incomplete method implementation.
        // Return the number of sections.
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete method implementation.
        // Return the number of rows in the section.
        return apostles.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let apostle = apostles[indexPath.row]
        let cell = tableView.dequeueReusableCell(withIdentifier: "subtitle", for: indexPath)
        
        // Configure the cell...
        
        cell.textLabel?.text = apostle.name
        cell.detailTextLabel?.text = apostle.nickname
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView,
                            accessoryButtonTappedForRowWith indexPath: IndexPath) {
        let apostle = apostles[indexPath.row]
        let title = apostle.name
        let message = apostle.funFact
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .actionSheet)
        let okayAction = UIAlertAction(title: "Okay", style: .default, handler: nil)
        alertController.addAction(okayAction)
        present(alertController, animated: true, completion: nil)
        self.tableView.deselectRow(at: indexPath, animated: true)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using [segue destinationViewController].
        // Pass the selected object to the new view controller.
        
        if let detailViewController = segue.destination as? ApostleDetailViewController {
            if let indexPath = self.tableView.indexPathForSelectedRow {
                detailViewController.apostle = apostles[indexPath.row]
            }
        }
    }
}

