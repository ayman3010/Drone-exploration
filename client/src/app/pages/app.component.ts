import { Component } from '@angular/core';
import { CommunicationService } from '../services/communication.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'client';

  constructor( private communicationService: CommunicationService){}
}
