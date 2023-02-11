import { HttpClient, HttpErrorResponse, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, of, throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';
import { environment } from 'src/environments/environment';
import { Drone } from '../classes/drone';
import {io , Socket} from 'socket.io-client';
import * as Rx from 'rxjs';

@Injectable({
    providedIn: 'root',
})
export class CommunicationService {
    private readonly baseUrl: string = environment.serverUrl;
    private socket: Socket;

    constructor(private http: HttpClient) {
      this.socket = io(this.baseUrl, { transports: ['websocket'], upgrade: false });
    };

    listen(eventName: string) {
      return new Observable((subsriber) => {
        this.socket.on(eventName, (data:any) => {
          subsriber.next(data);
        } )
      });
    };

    emit(eventName: string, ...data:any) {
      this.socket.emit(eventName, data);
    }

    logRequest(droneId: number): Observable<string> {
      return this.http.post<string>(this.baseUrl + "/log_request", {"id": droneId})
      .pipe(catchError(this.handleError));
    }
    
    private handleError(error: HttpErrorResponse) {
        if (error.status === 0) {
          console.error('An error occurred:', error.error);
        } else {
          console.error(
            `Backend returned code ${error.status}, body was: `, error.error);
        }
        return throwError(() => new Error('Something bad happened; please try again later.'));
      }
   
}

